/*
 * Cátedra: Electrónica Programable
 * FIUNER - 2018
 * Autor/es:
 * SMateos - smateos@ingenieria.uner.edu.ar
 *
 *
 *
 * Revisión:
 * 27-02-19: Versión inicial
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
#include "2_ContadorDeObjetos.h"

#include "systemclock.h"
#include "led.h"
#include "switch.h"
#include "lcditse0803.h"
#include "tcrt5000.h"
#include "buzzer.h"
#include "delay.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/
bool activ_flag = false;
uint16_t count = 0;
/*==================[internal functions declaration]=========================*/
void Switch1 (void)
{
	activ_flag = !activ_flag;
	LedToggle(LED_RGB_R);
	LedToggle(LED_RGB_G);
}

void Switch3 (void)
{
	count = 0;
	LcdItsE0803Write(count);
}

void SysInit(void)
{
	SystemClockInit();
	LedsInit();
	LcdItsE0803Init();
	Tcrt5000Init(GPIO_T_COL0);
	BuzzerInit();
	SwitchActivInt(SWITCH_1, Switch1);
	SwitchActivInt(SWITCH_3, Switch3);
	activ_flag = false;
    LedOn(LED_RGB_R);
}
/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	SysInit();
	while(1)
    {
		if(activ_flag)
		{
		    if(Tcrt5000ReadState())
		    {
		    	DelayMs(10);
		    	if(Tcrt5000ReadState())
		    	{
		    		count++;
			    	BuzzerOn();
			    	DelayMs(100);
			    	BuzzerOff();
		    		while(Tcrt5000ReadState());
		    	}
		    }
		    if(SWITCH_2 != SwitchesRead())
		    	LcdItsE0803Write(count);
		}
		else
			LcdItsE0803Off();
		DelayMs(500);
	}
    
	return 0;
}

/*==================[end of file]============================================*/

