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
#include "4_ADySerial.h"       /* <= own header */
#include "systemclock.h"
#include "led.h"
#include "switch.h"
#include "analog_io.h"
#include "timer.h"
#include "uart.h"
#include "arm_math.h"

/*==================[macros and definitions]=================================*/
#define AD_SAMPLE_FREC (1000/500)
#define DA_SAMPLE_FREC (1000/250)
#define ALPHA 0.111
#define TIMESAMP 0.002
#define BUFFER_SIZE 231

/*==================[internal data definition]===============================*/
uint8_t frec_filter = 10;
float32_t alpha;

const uint8_t ecg[BUFFER_SIZE]={
		76, 77, 78, 77, 79, 86, 81, 76, 84, 93, 85, 80,
		89, 95, 89, 85, 93, 98, 94, 88, 98, 105, 96, 91,
		99, 105, 101, 96, 102, 106, 101, 96, 100, 107, 101,
		94, 100, 104, 100, 91, 99, 103, 98, 91, 96, 105, 95,
		88, 95, 100, 94, 85, 93, 99, 92, 84, 91, 96, 87, 80,
		83, 92, 86, 78, 84, 89, 79, 73, 81, 83, 78, 70, 80, 82,
		79, 69, 80, 82, 81, 70, 75, 81, 77, 74, 79, 83, 82, 72,
		80, 87, 79, 76, 85, 95, 87, 81, 88, 93, 88, 84, 87, 94,
		86, 82, 85, 94, 85, 82, 85, 95, 86, 83, 92, 99, 91, 88,
		94, 98, 95, 90, 97, 105, 104, 94, 98, 114, 117, 124, 144,
		180, 210, 236, 253, 227, 171, 99, 49, 34, 29, 43, 69, 89,
		89, 90, 98, 107, 104, 98, 104, 110, 102, 98, 103, 111, 101,
		94, 103, 108, 102, 95, 97, 106, 100, 92, 101, 103, 100, 94, 98,
		103, 96, 90, 98, 103, 97, 90, 99, 104, 95, 90, 99, 104, 100, 93,
		100, 106, 101, 93, 101, 105, 103, 96, 105, 112, 105, 99, 103, 108,
		99, 96, 102, 106, 99, 90, 92, 100, 87, 80, 82, 88, 77, 69, 75, 79,
		74, 67, 71, 78, 72, 67, 73, 81, 77, 71, 75, 84, 79, 77, 77, 76, 76,
};

bool filter_on = true;

/*==================[internal functions declaration]=========================*/
/* @brief Lee el valor convertido del AD
 *
 */
void ReadData(){
	uint16_t buf;
	static uint16_t saved_data;
	AnalogInputRead(CH1, &buf);
	UartSendString(SERIAL_PORT_PC, UartItoa(buf, 10));
	if(filter_on)
	{
		UartSendString(SERIAL_PORT_PC, (uint8_t *) ",");
		buf = saved_data+alpha*(buf-saved_data);
		saved_data = buf;
		UartSendString(SERIAL_PORT_PC, UartItoa(buf, 10));
		UartSendString(SERIAL_PORT_PC, (uint8_t *) "\r");
	}
	else
	{
		UartSendString(SERIAL_PORT_PC, (uint8_t *) "\r");
	}
}

void StartConvertion () {
	AnalogStartConvertion();
}

void OutputECG () {
	static uint8_t i = 0;
	AnalogOutputWrite(ecg[i]);
	i++;
	if(i == BUFFER_SIZE)
	{
		i = 0;
	}
}

void Switch1 (void)
{
	filter_on = true;
}

void Switch2 (void)
{
	filter_on = false;
}

void Switch3 (void)
{
	frec_filter += 5;
	alpha = TIMESAMP/((1/(2*3.14*frec_filter))+TIMESAMP);
}

void Switch4 (void)
{
	frec_filter -= 5;
	alpha = TIMESAMP/((1/(2*3.14*frec_filter))+TIMESAMP);
}

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{

	analog_input_config AD_config;
	AD_config.input = CH1;
	AD_config.mode = AINPUTS_SINGLE_READ;
	AD_config.pAnalogInput = ReadData;

	timer_config timer_config_A;
	timer_config_A.timer = TIMER_A;
	timer_config_A.period = AD_SAMPLE_FREC;
	timer_config_A.pFunc = StartConvertion;

	timer_config timer_config_B;
	timer_config_B.timer = TIMER_B;
	timer_config_B.period = DA_SAMPLE_FREC;
	timer_config_B.pFunc = OutputECG;

	serial_config UART_USB;
	UART_USB.baud_rate = 115200;
	UART_USB.port = SERIAL_PORT_PC;
	UART_USB.pSerial = NULL;

	SystemClockInit();
	fpuInit();
	LedsInit();
	SwitchesInit();
	SwitchActivInt(SWITCH_1, Switch1);
	SwitchActivInt(SWITCH_2, Switch2);
	SwitchActivInt(SWITCH_3, Switch3);
	SwitchActivInt(SWITCH_4, Switch4);
	AnalogInputInit(&AD_config);
	AnalogOutputInit();
	TimerInit(&timer_config_A);
	TimerInit(&timer_config_B);
	UartInit(&UART_USB);
	TimerStart(TIMER_A);
	TimerStart(TIMER_B);

	alpha = TIMESAMP/((1/(2*3.14*frec_filter))+TIMESAMP);

    while(1){

	}
    
	return 0;
}

/*==================[end of file]============================================*/

