/*
 * Cátedra: Electrónica Programable
 * FIUNER - 2019
 * Autor/es:
 *
 *
 *
 * Revisión:
 * 02-10-18: Versión inicial SM
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*==================[inclusions]=============================================*/
#include "4_ADyFFT.h"       /* <= own header */
#include "systemclock.h"
#include "led.h"
#include "analog_io.h"
#include "timer.h"
#include "fpu_init.h"

#define ARM_MATH_CM4
#define __FPU_PRESENT 1
#include "arm_math.h"
#include "arm_const_structs.h"

#define IFFT_FLAG 0
#define DO_BIT_REVERSE 1

#define WINDOW_WIDTH 128

#define SAMPLE_FREC_US (1000000/6000)

bool new_window = false;
float32_t signal[2*WINDOW_WIDTH];

/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/
/* @brief Lee el valor convertido del AD
 *
 */
void ReadData(){
	static uint8_t i = 0;
	uint16_t buf;
	AnalogInputRead(CH1, &buf);
	if(i<WINDOW_WIDTH){
		signal[i*2] = buf*(3.3/1024); /* Parte real */
		signal[i*2+1] = 0; /* Parte imaginaria */
		i++;
	}
	else{
		i = 0;
		new_window = true;
	}
}

void StartConvertion () {
	AnalogStartConvertion();
}
/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	uint8_t i, i_max;
	float32_t fft[WINDOW_WIDTH], max = 0;

	analog_input_config AD_config;
	AD_config.input = CH1;
	AD_config.mode = AINPUTS_SINGLE_READ;
	AD_config.pAnalogInput = ReadData;

	timer_config timer_config;
	timer_config.timer = TIMER_C;
	timer_config.period = SAMPLE_FREC_US;
	timer_config.pFunc = StartConvertion;

	SystemClockInit();
	fpuInit();
	LedsInit();
	AnalogInputInit(&AD_config);
	TimerInit(&timer_config);
	TimerStart(TIMER_C);

    while(1){
    	if(new_window){

    		/* Procesamiento para realizar la FFT */
    		arm_cfft_f32(&arm_cfft_sR_f32_len128, signal, IFFT_FLAG, DO_BIT_REVERSE);
    		arm_cmplx_mag_f32(signal, fft, WINDOW_WIDTH);
    		new_window = false;

    		/* Obtencion del valor maximo del espectro de frecuencias */
    		for(i=2 ; i<WINDOW_WIDTH ; i++){
    			if(fft[i]>max){
    				max = fft[i];
    				i_max = i;
    			}
    		}
    		max = 0;

    		/* Prende distintos leds segun en que rango de frecuencias se encuentre el maximo */
    		LedsOffAll();
    		if (i_max < 15)
    			LedOn(LED_3);
    		else if (i_max < 25)
    			LedOn(LED_2);
    		else if (i_max < 35)
    			LedOn(LED_1);
    		else if (i_max < 45)
    			LedOn(LED_RGB_B);
    		else
    			LedsOffAll();

    	}
	}
    
	return 0;
}

/*==================[end of file]============================================*/

