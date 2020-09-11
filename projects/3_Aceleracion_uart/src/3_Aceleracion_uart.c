/* Copyright 2018,
 * Sebastian Mateos
 * sebastianantoniomateos@gmail.com
 * Cátedra Electrónica Programable
 * Facultad de Ingeniería
 * Universidad Nacional de Entre Ríos
 * Argentina
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

/** \brief Bare Metal aplication for MMA8451 in the EDU-CIAA board.
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 * SM		Sebastian Mateos
 */

/*
 * modification history (new versions first)
 *  20180320 v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "3_Aceleracion_uart.h"       /* <= own header */
#include "systemclock.h"
#include "led.h"
#include "switch.h"
#include "uart.h"
#include "i2c.h"
#include "MMA8451.h"


/*==================[macros and definitions]=================================*/
#define COUNT_DELAY 300000


/*==================[internal functions declaration]=========================*/
void Delay(void);


void Delay(void)
{
	uint32_t i;

	for(i=COUNT_DELAY; i!=0; i--)
	{
		   asm  ("nop");
	}
}

int main(void)
{
	uint32_t tecla;
	uint8_t pool = 0;
	uint8_t x,y,z;

	serial_config UART_USB;
	UART_USB.baud_rate = 115200;
	UART_USB.port = SERIAL_PORT_PC;
	UART_USB.pSerial = NULL;

	SystemClockInit();
	LedsInit();
	SwitchesInit();
	UartInit(&UART_USB);
	Init_I2c(100000); /*Inicializa el modulo i2c a una frecuencia de 100KHz*/

	UartSendString(SERIAL_PORT_PC, "Interfaz de prueba del modulo MMMA8451\r\n");
	UartSendString(SERIAL_PORT_PC, "Tecla 1: Verifica comunicación con el modulo\r\n");
	UartSendString(SERIAL_PORT_PC, "Tecla 2: Realiza la configuracion por defecto del modulo\r\n");
	UartSendString(SERIAL_PORT_PC, "Tecla 3: Lee una vez los valores de aceleracion\r\n");
	UartSendString(SERIAL_PORT_PC, "Tecla 4: Pooling de lectur de aceleracion\r\n");

	while(1)
	{
		tecla = SwitchesRead();
		switch(tecla)
		{
			case SWITCH_1:
				LedOn(LED_RGB_B);
				while(SwitchesRead() == SWITCH_1);
				if(MMA8451IsAlive())
					UartSendString(SERIAL_PORT_PC, "MMA8451 conectado\r\n");
				else
					UartSendString(SERIAL_PORT_PC, "No se ha encontrado el modulo MMA8451\r\n");
				LedOff(LED_RGB_B);
			break;
			case SWITCH_2:
				LedOn(LED_1);
				while(SwitchesRead() == SWITCH_2);
				mma8451_config_t config;
				MMA8451PrepareDefaultConfig(&config);
				if(MMA8451Config(config)==1)
					UartSendString(SERIAL_PORT_PC, "Se ha configurado correctamente el modulo MMA8451\r\n");
				else
					UartSendString(SERIAL_PORT_PC, "No se ha podido configurado correctamente el modulo MMA8451\r\n");
				LedOff(LED_1);
			break;
			case SWITCH_3:
				LedOn(LED_2);
				while(SwitchesRead() == SWITCH_3)
				{
					DelayMs(500);
					MMA8451Read(&x,&y,&z);
					if(x & 0x80)
					{
						x ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((x & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "X ");
					if(y & 0x80)
					{
						y ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((y & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "Y ");
					if(z & 0x80)
					{
						z ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((z & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "Z\r\n");
				}
				LedOff(LED_2);

			break;
			case SWITCH_4:
				LedOn(LED_3);
				while(SwitchesRead() == SWITCH_4);
				pool = 1;
				while(pool == 1)
				{
					DelayMs(500);
					MMA8451Read(&x,&y,&z);
					if(x & 0x80)
					{
						x ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((x & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "X ");
					if(y & 0x80)
					{
						y ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((y & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "Y ");
					if(z & 0x80)
					{
						z ^= 0xFF;
						UartSendString(SERIAL_PORT_PC, "-");
					}
					UartSendString(SERIAL_PORT_PC, UartItoa((z & 0x7F),10));
					UartSendString(SERIAL_PORT_PC, "Z\r\n");
					if(SwitchesRead()==SWITCH_4)
					{
						while(SwitchesRead() == SWITCH_4);
						pool = 0;
					}
				}
				LedOff(LED_3);
			break;
		}
	}
	return 0;
}

/*==================[end of file]============================================*/

