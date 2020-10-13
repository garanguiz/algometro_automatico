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
#include "../inc/5_celda_de_carga.h"       /* <= own header */
#include "uart.h"
#include "load_cell_30.h"

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
	// Inicialización del puerto UART

	serial_config UART_USB;
	UART_USB.baud_rate = 115200;
	UART_USB.port = SERIAL_PORT_PC;
	UART_USB.pSerial = NULL;

	UartInit(&UART_USB);

	Ready4read(); //Esperar a que esté listo para leer, y recién ahí salir de esta función

}

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

int main(void)
{

	SysInit();
	uint32_t i;
	i=1;

    while(1)
    {
    	uint32_t valor;
    	valor=ReadCount();

    	if(i%1==0){ //Simplemente un divisor de frecuencia de salida de datos

    		if(valor==0){
    			    		UartSendString(SERIAL_PORT_PC,"No hay carga \r\n");
    					}

    		if(valor!=0){
    						valor=((valor+2552)/17);
    						UartSendString(SERIAL_PORT_PC,"EL PESO ES DE: ");
    						UartSendString(SERIAL_PORT_PC,UartItoa(valor,10));
    						UartSendString(SERIAL_PORT_PC," gramos \r\n");
    					}
    			  }

    	i++;
	}

    
}

/*==================[end of file]============================================*/

