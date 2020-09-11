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
#include "2_DistanceRS485.h"
#include "systemclock.h"
#include "led.h"
#include "switch.h"
#include "uart.h"
#include "hc_sr04.h"
#include "delay.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

void SysInit(void)
{
	serial_config UART_RS485;
	UART_RS485.baud_rate = 115200;
	UART_RS485.port = SERIAL_PORT_RS485;
	UART_RS485.pSerial = NULL;

	serial_config UART_USB;
	UART_USB.baud_rate = 115200;
	UART_USB.port = SERIAL_PORT_PC;
	UART_USB.pSerial = NULL;

	SystemClockInit();
	LedsInit();
	SwitchesInit();
	LcdItsE0803Init();
	UartInit(&UART_USB);
	UartInit(&UART_RS485);
	HcSr04Init(T_FIL2, GPIO_T_FIL3);
}
/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{
	SysInit();
	uint16_t distance;

	while(1)
    {
		distance = HcSr04ReadDistanceInCentimeters();
		UartSendString(SERIAL_PORT_PC, UartItoa(distance,10));
		UartSendString(SERIAL_PORT_PC, "\n\r");
		UartSendString(SERIAL_PORT_RS485, UartItoa(distance,10));
		UartSendString(SERIAL_PORT_RS485, "\n\r");
		LcdItsE0803Write(distance);
		DelayMs(1000);
	}
    
	return 0;
}

/*==================[end of file]============================================*/

