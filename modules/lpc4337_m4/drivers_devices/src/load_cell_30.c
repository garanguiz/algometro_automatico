	/*********************************************************************
 * Copyright 2019,
 * Facundo Urteaga
 * facundonahuelurteaga@gmail.com
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
 ***************************************************************************//*!
*
* @file      load_cell_30.c
*
* @author    Facundo Urteaga
*
* @brief     Driver para celda de carga mediante módulo HX711
*
*
*
******************************************************************************/

/*==================[inclusions]=============================================*/
#include "load_cell_30.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
static uint32_t tara=0; /**< Valor a restarse del dato crudo, se actualiza con la función Tarar. */

const float escala=0.0001013043268446132f;/**< Convierte el dato crudo a kPa, para la celda de carga tipo botón FX29*/
//Celda 30 kg: 0.0064617f (para convertir a GRAMOS)
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

/**
 * @brief Función que espera a que el DOUT del HX711 esté listo para enviar datos.
 *
 * Se inicializan los puertos para la comunicación con el módulo HX711, y espera hasta que éste presente una lectura.
 */
void Ready4read(void)
{

	GPIOInit(GPIO_TXD0_DT, GPIO_INPUT); //DOUT // Inicializar Pines de entrada y salida
	GPIOInit(GPIO_TXD1_SCK, GPIO_OUTPUT); //PD_SCLK
	while(GPIORead(GPIO_TXD0_DT)); // Lee DOUT. Para habilitar lectura debe estar en bajo (=0)

}

/**
 * @brief Función que devuelve cero o un valor proporcional a la presión si es positivo.
 *
 * Realiza la secuencia para la lectura de datos y lo convierte según la escala y el valor de tara.
 *
 * @return Valor de presión en kPa, tarado.
 */
uint32_t ReadCount(void)
{
	uint32_t Count;
	uint32_t i;
	GPIOOff(GPIO_TXD1_SCK);
	Count=0;
	while(GPIORead(GPIO_TXD0_DT));
	for (i=0;i<24;i++)
	{
			GPIOOn(GPIO_TXD1_SCK);
			Count=Count<<1;
			GPIOOff(GPIO_TXD1_SCK);
				if(GPIORead(GPIO_TXD0_DT))
				{
					Count++;
				}
	}
	GPIOOn(GPIO_TXD1_SCK);

		//Si quiero considerar fuerzas positivas y negativas:

		/* if(Count>=0b100000000000000000000000){
		Count=Count^0xFFFFFF; //XOR por vector de 1s
		Count++; //Sumo 1, acá tendría el numero binario positivo
		Count=(8388608-Count)/1000;} //Me desprendo del signo sumandole el rango inferior

		if(Count<0b100000000000000000000000){
		Count=Count=Count^0x800000; //Le quito el signo
		Count=(Count+8388608)/1000; // Le sumo el rango inferior
		GPIOOff(GPIO_3);} */

		//Despreciando el módulo:

	if(Count<0b100000000000000000000000) //Si es negativo, lo fuerzo a cero
		{Count=0;}

	if(Count>=0b100000000000000000000000){
		Count=Count^0xFFFFFF; //XOR por vector de 1s
		Count--; //Resto 1, acá tendría el numero binario positivo
	} //Me desprendo del signo sumandole el rango inferior

	GPIOOff(GPIO_TXD1_SCK); //Hay que volver a bajarlo. Si lo dejás en alto por más de 60ms se apaga y tiene que volver a iniciarse, por eso tardaba.
	//Podemos apagarlo con alguna otra función, cuando no estemos graficando. Por ahora queda siempre prendido.
	return((Count*escala)-tara); //Al escalar se hace flotante pero luego convierte a uint32_t (creo)

}

/**
 * @brief Función que actualiza el valor de tara promediando n lecturas.
 *
 * @param n Número de lecturas a promediar.
 */
void Tarar(int n){//Tara promediando n lecturas
	tara = 0;
	uint32_t i;
	uint32_t acum = 0;
	for(i=0; i<n; i++){
		acum += ReadCount();
	}
	tara = acum/n;
}


/*==================[end of file]============================================*/
