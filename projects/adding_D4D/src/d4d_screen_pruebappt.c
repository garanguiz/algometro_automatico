/**************************************************************************
* 
* Copyright 2014 by Petr Gargulak. eGUI Community.
* Copyright 2009-2013 by Petr Gargulak. Freescale Semiconductor, Inc.
*
***************************************************************************
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License Version 3 
* or later (the "LGPL").
*
* As a special exception, the copyright holders of the eGUI project give you
* permission to link the eGUI sources with independent modules to produce an
* executable, regardless of the license terms of these independent modules,
* and to copy and distribute the resulting executable under terms of your 
* choice, provided that you also meet, for each linked independent module,
* the terms and conditions of the license of that module.
* An independent module is a module which is not derived from or based 
* on this library. 
* If you modify the eGUI sources, you may extend this exception 
* to your version of the eGUI sources, but you are not obligated 
* to do so. If you do not wish to do so, delete this
* exception statement from your version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You should have received a copy of the GNU General Public License
* and the GNU Lesser General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************//*!
*
* @file      d4d_screen_main.c
*
* @author    Petr Gargulak
* 
* @version   0.0.3.0
* 
* @date      Jan-14-2014
* 
* @brief     D4D driver - main screen source file of eGUI/D4D demo application
*
******************************************************************************/

#include "../d4d/d4d.h" //JB
#include "fonts.h" //JB
#include "../d4d/graphic_objects/d4d_label.c"
#include "../d4d/graphic_objects/d4d_graph.c"
#include "../d4d/graphic_objects/d4d_console.c"
#include "led.h"
#include "actuador_festo.h"
#include "load_cell_30.h"
#include "uart.h"
#include "variables_globales.h"
#include "stdlib.h"



/*****************************************************************************
*
* Graphic objects coordination specifications
*
*
*****************************************************************************/
#define EDGE_SPACE	2

// Label object - Título

#define LBL_TIT_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/4 + 3*EDGE_SPACE)
#define LBL_TIT_POSY EDGE_SPACE

#define LBL_TIT_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/2 - 4*EDGE_SPACE)
#define LBL_TIT_SIZEY 70

// Label object - Iniciar/Parar

#define LBL_IP_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/2 + EDGE_SPACE)
#define LBL_IP_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-40-EDGE_SPACE)

#define LBL_IP_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_IP_SIZEY 40

// Label object - Parar y salir

#define LBL_PS_POSX (D4D_SCREEN_SIZE_LONGER_SIDE*3/4 + EDGE_SPACE)
#define LBL_PS_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-40-EDGE_SPACE)

#define LBL_PS_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_PS_SIZEY 40

// Console object - Estado

#define CNSL_EST_POSX 2
#define CNSL_EST_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE - 90 - 2*EDGE_SPACE)

#define CNSL_EST_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE-(2 * EDGE_SPACE))
#define CNSL_EST_SIZEY 40

#define CNSL_EST_LINE_CNT 1
#define CNSL_EST_CHAR_CNT 45

// Label object - Presión

#define LBL_PRE_POSX (EDGE_SPACE)
#define LBL_PRE_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-50-EDGE_SPACE)

#define LBL_PRE_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - EDGE_SPACE - 15)
#define LBL_PRE_SIZEY 50

// Label object - kPa

#define LBL_KPA_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/4 + 100)
#define LBL_KPA_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE - 50 - EDGE_SPACE)

#define LBL_KPA_SIZEX (100 - EDGE_SPACE)
#define LBL_KPA_SIZEY 50

// Console object - Presión

#define CNSL_PRE_POSX (LBL_PRE_SIZEX+EDGE_SPACE)
#define CNSL_PRE_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-50-EDGE_SPACE)

#define CNSL_PRE_SIZEX 130
#define CNSL_PRE_SIZEY 50

#define CNSL_PRE_LINE_CNT 1
#define CNSL_PRE_CHAR_CNT 4

// Console object - Historial

#define CNSL_HIS_POSX (D4D_SCREEN_SIZE_LONGER_SIDE - 100 - EDGE_SPACE)
#define CNSL_HIS_POSY (70 + 2*EDGE_SPACE)

#define CNSL_HIS_SIZEX 100
#define CNSL_HIS_SIZEY (D4D_SCREEN_SIZE_SHORTER_SIDE - CNSL_PRE_SIZEY - LBL_TIT_SIZEY - CNSL_EST_SIZEY - (6*EDGE_SPACE))

#define CNSL_HIS_LINE_CNT 20
#define CNSL_HIS_CHAR_CNT 10

// Graph object - Gráfica de presión

#define GRAPH_POSX EDGE_SPACE
#define GRAPH_POSY (70 + 2*EDGE_SPACE)

#define GRAPH_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE - (3 * EDGE_SPACE) - CNSL_HIS_SIZEX)
#define GRAPH_SIZEY (D4D_SCREEN_SIZE_SHORTER_SIDE - CNSL_PRE_SIZEY - LBL_TIT_SIZEY - CNSL_EST_SIZEY - (6*EDGE_SPACE))



/*****************************************************************************
*
* Graphic objects callback/events functions declaration
*
*
*****************************************************************************/



/*****************************************************************************
*
* Graphic object declarations
*
*
*****************************************************************************/
// Label título
D4D_DECLARE_STD_RLABEL(scrPruebappt_lblTitle, "PRUEBA DE PPT", LBL_TIT_POSX, LBL_TIT_POSY, LBL_TIT_SIZEX, LBL_TIT_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12_BIG)

// Label Iniciar/Parar
D4D_DECLARE_STD_RLABEL(scrPruebappt_lblIniciarParar, "Iniciar/Parar", LBL_IP_POSX, LBL_IP_POSY, LBL_IP_SIZEX, LBL_IP_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12)

// Label Parar y salir
D4D_DECLARE_STD_RLABEL(scrPruebappt_lblPararSalir, "Parar y Salir", LBL_PS_POSX, LBL_PS_POSY, LBL_PS_SIZEX, LBL_PS_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12)

// Console estado
D4D_DECLARE_STD_CONSOLE(scrPruebappt_cnslEstado, CNSL_EST_POSX, CNSL_EST_POSY, CNSL_EST_SIZEX, CNSL_EST_SIZEY, CNSL_EST_LINE_CNT, CNSL_EST_CHAR_CNT, FONT_BERLIN_SANS_FBDEMI12_HIGH)

// Label Presión
D4D_DECLARE_STD_LABEL(scrPruebappt_lblPresion, "PRESION: ", LBL_PRE_POSX, LBL_PRE_POSY, LBL_PRE_SIZEX, LBL_PRE_SIZEY, FONT_BERLIN_SANS_FBDEMI12_BIG)

// Label kPa
D4D_DECLARE_STD_LABEL(scrPruebappt_lblKPa, "kPa", LBL_KPA_POSX, LBL_KPA_POSY, LBL_KPA_SIZEX, LBL_KPA_SIZEY, FONT_BERLIN_SANS_FBDEMI12_BIG)

// Console presion
D4D_DECLARE_STD_CONSOLE(scrPruebappt_cnslPresion, CNSL_PRE_POSX, CNSL_PRE_POSY, CNSL_PRE_SIZEX, CNSL_PRE_SIZEY, CNSL_PRE_LINE_CNT, CNSL_PRE_CHAR_CNT, FONT_BERLIN_SANS_FBDEMI12_BIG)

// Console historial
D4D_DECLARE_STD_CONSOLE(scrPruebappt_cnslHistorial, CNSL_HIS_POSX, CNSL_HIS_POSY, CNSL_HIS_SIZEX, CNSL_HIS_SIZEY, CNSL_HIS_LINE_CNT, CNSL_HIS_CHAR_CNT, FONT_BERLIN_SANS_FBDEMI12)

// Graph
Byte dataTrace[617];

D4D_DECLARE_STD_RGRAPH_BEGIN(scrPruebappt_graph, "PRESION", GRAPH_POSX, GRAPH_POSY, GRAPH_SIZEX, GRAPH_SIZEY, 8, 9, 4, 20, FONT_ARIAL7, FONT_ARIAL7)
  D4D_DECLARE_GRAPH_TRACE(dataTrace, D4D_COLOR_BLUE, D4D_LINE_THICK, D4D_GRAPH_TRACE_TYPE_LINE)
D4D_DECLARE_GRAPH_END()

/*****************************************************************************
*
* eGUI/D4D screen declaration
*
*
*****************************************************************************/

// Standard screen declaration
D4D_DECLARE_STD_SCREEN_BEGIN(screen_pruebappt, ScreenPruebappt_)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_lblTitle)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_lblIniciarParar)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_lblPararSalir)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_cnslEstado)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_graph)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_cnslPresion)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_lblPresion)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_lblKPa)
	D4D_DECLARE_SCREEN_OBJECT(scrPruebappt_cnslHistorial)
D4D_DECLARE_SCREEN_END()    

/*****************************************************************************
*
* Local variables 
*
*
*****************************************************************************/
//Byte valor=0;
//Byte sube_1_baja_0=1;
static int iniciar = D4D_FALSE;
static int secuencia = 0;
char presion[5];

//ecg
//Byte senial[617]={100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
//Byte* pDummyMusic=senial;
uint32_t dato;
//static uint32_t tiempo_ms;
//static uint32_t inicio_tiempo;


/*****************************************************************************
*
* Local function 
*
*
*****************************************************************************/


/*****************************************************************************
*
* Screen system functions 
*
*
*****************************************************************************/

// One time called screen function in screen initialization process
static void ScreenPruebappt_OnInit()
{
	D4D_GraphSetDataWidth(&scrPruebappt_graph, 400);
}

// Screen on Activate function called with each screen activation
static void ScreenPruebappt_OnActivate()
{
	D4D_CnslClearAll(&scrPruebappt_cnslEstado);
	D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: preparado.");
	D4D_CnslPutString(&scrPruebappt_cnslHistorial, "Historial\n\r");
	ActuadorEnable(TRUE);
	iniciar = D4D_FALSE;
	pulsado = FALSE;
	secuencia = 0;
}

// Screen "Main" function called periodically in each D4D_poll runs
static void ScreenPruebappt_OnMain()
{
	if(iniciar){

    	if(secuencia==1){
    		Tarar(20);
    		tiempo_ms = 0;
//    		StopWatch_Init();
//    		inicio_tiempo = StopWatch_Start();
    		secuencia += 1;
    	}

    	if(secuencia==0){//Mostrar mensaje "tarando"
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: tarando.");
    		secuencia++;//Para que complete la primera vuelta antes de tarar, así muestra el mensaje "tarando"
    	}

    	if(pulsado){
    		iniciar = D4D_FALSE;
    		LedOff(LED_RGB_B);
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: prueba detenida (pa.) a los ");
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, presion);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, " kPa.");
    		D4D_CnslPutString(&scrPruebappt_cnslHistorial, presion);
    		D4D_CnslPutString(&scrPruebappt_cnslHistorial, " kPa\n\r");
    		secuencia=0;
    	}
    	dato=ReadCount();
		D4D_GraphAddTraceData(&scrPruebappt_graph, 0, -(dato/2)-1); //-1 para que no quede el 0 arriba (en la gráfica)
		UartSendString(SERIAL_PORT_PC,UartItoa(tiempo_ms,10));
		UartSendString(SERIAL_PORT_PC,"\t");
    	UartSendString(SERIAL_PORT_PC,UartItoa(dato,10));
    	UartSendString(SERIAL_PORT_PC,"\r\n");
    	D4D_CnslClearAll(&scrPruebappt_cnslPresion);
    	itoa(dato,presion,10);
    	D4D_CnslPutString(&scrPruebappt_cnslPresion, presion);

    	if(secuencia==2){
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: efectuando homing.");
			MoverActuador(HOMING);
			secuencia += 1;
		}
		if(MotionComplete()&&(secuencia==3)){
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: buscando contacto.");
			MoverActuador(CONTACTO);
			secuencia += 1;
		}
		if((MotionComplete()||dato>10)&&(secuencia==4)){
			GPIOToggle(GPIO_SPI_MOSI_TRIG);
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: presionando.");
			MoverActuador(AVAN1);
			secuencia += 1;
		}
		if(MotionComplete()&&(secuencia==5)){
    		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
    		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: retrocediendo.");
			MoverActuador(RETRO);
			secuencia += 1;
		}
		if(MotionComplete()&&(secuencia==6)){
			iniciar=D4D_FALSE;
			LedOff(LED_RGB_B);
			D4D_CnslClearAll(&scrPruebappt_cnslEstado);
			D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: limite alcanzado (");
			D4D_CnslPutString(&scrPruebappt_cnslEstado, presion);
			D4D_CnslPutString(&scrPruebappt_cnslEstado, " kPa).");

			secuencia=0;
		}
	}
}


// Screen on DeActivate function called with each screen deactivation
static void ScreenPruebappt_OnDeactivate()
{
	if(iniciar==D4D_TRUE){
		iniciar=D4D_FALSE;
		LedOff(LED_RGB_B);
		MoverActuador(RETRO);
		D4D_CnslClearAll(&scrPruebappt_cnslEstado);
		D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: prueba detenida.");
	}
	D4D_GraphClearAll(&scrPruebappt_graph);
	D4D_CnslClearAll(&scrPruebappt_cnslPresion);
	D4D_CnslClearAll(&scrPruebappt_cnslHistorial);
	secuencia=0;
	while(!MotionComplete());
	ActuadorEnable(FALSE);
}

// Screen on message function called with each internal massage for this screen
static Byte ScreenPruebappt_OnObjectMsg(D4D_MESSAGE* pMsg)
{
  if(pMsg->nMsgId == D4D_MSG_KEYDOWN)
  	  {
  		  if(pMsg->prm.key == D4D_KEY_SCANCODE_ENTER)
  		  {
  			  if(!iniciar){
  				  iniciar=D4D_TRUE;
  				  LedOn(LED_RGB_B);
  				  pulsado = FALSE;
  			  }
  			  else{
  				  MoverActuador(RETRO);
  				  GPIOToggle(GPIO_SPI_MOSI_TRIG);
  				  iniciar=D4D_FALSE;
  				  LedOff(LED_RGB_B);
  				  D4D_CnslClearAll(&scrPruebappt_cnslEstado);
  				  D4D_CnslPutString(&scrPruebappt_cnslEstado, "Estado: prueba detenida (op.) a los ");
  				  D4D_CnslPutString(&scrPruebappt_cnslEstado, presion);
  				  D4D_CnslPutString(&scrPruebappt_cnslEstado, " kPa.");
  				  secuencia=0;
  			  }
  		  }
  	  }
  return 0;
}




