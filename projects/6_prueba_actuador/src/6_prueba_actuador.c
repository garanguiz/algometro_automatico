/*
 * Cátedra: Electrónica Programable
 * FIUNER - 2018
 * Autor/es:
 * JMReta - jmreta@ingenieria.uner.edu.ar
 *
 *
 *
 * Revisión:
 * 07-02-18: Versión inicial
 * 01-04-19: V1.1 SM
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
#include "../inc/6_prueba_actuador.h"       /* <= own header */
#include "gpio.h"
#include "delay.h"

/*==================[macros and definitions]=================================*/
// #define COUNT_DELAY 3000000
/*==================[internal data definition]===============================*/

/* void Delay(void)
{
	uint32_t i;

	for(i=COUNT_DELAY; i!=0; i--)
	{
		   asm  ("nop");
	}
}
*/
/*==================[internal functions declaration]=========================*/


void SysInit(void)
{
	// Inicialización del GPIO y el clock

	SystemClockInit();
	GPIOInit(GPIO_RXD1_ENABLE,GPIO_OUTPUT);
	GPIOInit(GPIO_TX_EN_START,GPIO_OUTPUT);
	GPIOInit(GPIO_MDC_BIT0,GPIO_OUTPUT);
	GPIOInit(GPIO_CRS_DV_BIT1,GPIO_OUTPUT);
	GPIOInit(GPIO_MDIO_BIT2,GPIO_OUTPUT);

}

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{

	SysInit();

    while(1)
    {
    	/*Enable*/
    	GPIOOn(GPIO_RXD1_ENABLE);
    	DelaySec(2);

    	/*Homing*/
    	GPIOOff(GPIO_MDC_BIT0);
    	GPIOOff(GPIO_CRS_DV_BIT1);
    	DelaySec(1);
    	GPIOOn(GPIO_TX_EN_START);
    	DelaySec(12);
    	GPIOOff(GPIO_TX_EN_START);

    	/*Tarea1: paso a 30mm en alta velocidad*/
    	GPIOOn(GPIO_MDC_BIT0);
    	DelaySec(1);
    	GPIOOn(GPIO_TX_EN_START);
    	DelaySec(7);
    	GPIOOff(GPIO_TX_EN_START);

    	/*Tarea2: Paso a 15mm en baja velocidad*/
    	GPIOOn(GPIO_CRS_DV_BIT1);
    	DelaySec(1);
    	GPIOOn(GPIO_TX_EN_START);
    	DelaySec(7);
    	GPIOOff(GPIO_TX_EN_START);

    	/*Bajo enable*/
    	GPIOOff(GPIO_RXD1_ENABLE);
    	DelaySec(1);
	}

    
}

/*==================[end of file]============================================*/

