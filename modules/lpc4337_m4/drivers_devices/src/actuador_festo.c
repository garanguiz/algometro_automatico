/*********************************************************************
 *  Copyright 2019,
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
 ****************************************************************************//*!
*
* @file      actuador_festo.c
*
* @author    Facundo Urteaga
*
* @brief     Driver para el controlador Festo CMMO-ST y el actuador EPCO
*
*
*
******************************************************************************/

/*==================[inclusions]=============================================*/
#include "actuador_festo.h"
#include "delay.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/
/**
 * @brief Inicialización de los puertos para el driver.
 */
void InitActuador(void){
	GPIOInit(GPIO_RXD1_ENABLE,GPIO_OUTPUT);
	GPIOInit(GPIO_TX_EN_START,GPIO_OUTPUT);
	GPIOInit(GPIO_MDC_BIT0,GPIO_OUTPUT);
	GPIOInit(GPIO_CRS_DV_BIT1,GPIO_OUTPUT);
	GPIOInit(GPIO_MDIO_BIT2,GPIO_OUTPUT);
	GPIOInit(GPIO_8_MOTCOMP,GPIO_INPUT);
}

/**
 * @brief Envía una instrucción a ejecutar por el actuador.
 *
 * @param f Frase de la instrucción deseada.
 */
void MoverActuador(frase f){
	//Start baja
	GPIOOff(GPIO_TX_EN_START);
	DelayMs(15);
	//Seteo frase
	GPIOState(GPIO_MDC_BIT0,(f & 0x1));
	GPIOState(GPIO_CRS_DV_BIT1,(f & 0x2));
	GPIOState(GPIO_MDIO_BIT2,(f & 0x4));
	//Start sube (antes, requiere un retardo)
	DelayMs(15);//Debe ser mayor o igual a 2 ms + 10 ms (contacto relé)
	GPIOOn(GPIO_TX_EN_START);
	DelayMs(15); //Otro retardo para dar tiempo a que MOTION COMPLETE baje
}

//El retroceso se ejecuta como una instrucción más en MoverActuador.
void RetroActuador(void){

}
/**
 * @brief Informa el estado de la señal "motion complete".
 * @return TRUE si se completó el movimiento, FALSE en otro caso.
 */
bool MotionComplete(void){
	return(!(GPIORead(GPIO_8_MOTCOMP)));
}

/**
 * @brief Cambia el estado de la señal "enable".
 * @param estado TRUE para pasar a estado alto, FALSE para estado bajo.
 */
void ActuadorEnable(bool estado){
	if(estado)
		GPIOOn(GPIO_RXD1_ENABLE);
	else
		GPIOOff(GPIO_RXD1_ENABLE);
}
/*==================[end of file]============================================*/
