/*************************************************************************
 *  Copyright 2019,
 * Sebastian Mateos
 * smateos@ingenieria.uner.edu.ar
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
#ifndef ACTUADOR_FESTO_H
#define ACTUADOR_FESTO_H


/*==================[inclusions]=============================================*/
#include <stdint.h>
#include "gpio.h"
#include "bool.h"

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/
/**
 * @brief Codificación de las instrucciones en binario.
 */
typedef enum{
	HOMING=0,//!< HOMING
	CONTACTO,//!< CONTACTO
	AVAN1,   //!< AVAN1
	AVAN2,   //!< AVAN2
	AVAN3,   //!< AVAN3
	AVAN4,   //!< AVAN4
	AVAN5,   //!< AVAN5
	RETRO    //!< RETRO
}frase;
/*==================[external data declaration]==============================*/


/*==================[external functions declaration]=========================*/

/** @brief Initialization function */
void InitActuador(void);

void MoverActuador(frase f);
void RetroActuador(void);
bool MotionComplete(void);
void ActuadorEnable(bool estado);

/*==================[end of file]============================================*/
#endif /* #ifndef ACTUADOR_FESTO_H */

