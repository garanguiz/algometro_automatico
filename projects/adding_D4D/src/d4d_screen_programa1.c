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
//#include "../d4d/graphic_objects/d4d_label.c"
//#include "../d4d/graphic_objects/d4d_graph.c"
//#include "../d4d/graphic_objects/d4d_console.c"
#include "led.h"
#include "actuador_festo.h"

extern unsigned int flag100ms;



/*****************************************************************************
*
* Graphic objects coordination specifications
*
*
*****************************************************************************/
// Label object - Título

#define LBL_TIT_POSX 5
#define LBL_TIT_POSY 2

#define LBL_TIT_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE-10)
#define LBL_TIT_SIZEY 40

// Label object - Iniciar/Parar

#define LBL_IP_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/2 + EDGE_SPACE)
#define LBL_IP_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-45)

#define LBL_IP_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_IP_SIZEY 40

// Label object - Parar y salir

#define LBL_PS_POSX (D4D_SCREEN_SIZE_LONGER_SIDE*3/4 + EDGE_SPACE)
#define LBL_PS_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-45)

#define LBL_PS_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_PS_SIZEY 40

// Console object - Estado

#define CNSL_EST_POSX 2
#define CNSL_EST_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-100)

#define CNSL_EST_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE-(2 * EDGE_SPACE))
#define CNSL_EST_SIZEY 40

#define CNSL_EST_LINE_CNT 1
#define CNSL_EST_CHAR_CNT 40

// Graph object "Input audio Signal"

#define EDGE_SPACE	2

#define GRAPH_POSX 5
#define GRAPH_POSY 45

#define GRAPH_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE - (2 * EDGE_SPACE))
#define GRAPH_SIZEY (D4D_SCREEN_SIZE_SHORTER_SIDE - (2 * EDGE_SPACE) - GRAPH_POSY - 100)



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
D4D_DECLARE_STD_LABEL(scrPrograma1_lblTitle, "PROGRAMA 1", LBL_TIT_POSX, LBL_TIT_POSY, LBL_TIT_SIZEX, LBL_TIT_SIZEY, FONT_BERLIN_SANS_FBDEMI12_HIGH)

// Label Iniciar/Parar
D4D_DECLARE_STD_LABEL(scrPrograma1_lblIniciarParar, "Iniciar/Parar", LBL_IP_POSX, LBL_IP_POSY, LBL_IP_SIZEX, LBL_IP_SIZEY, FONT_BERLIN_SANS_FBDEMI12)

// Label Parar y salir
D4D_DECLARE_STD_LABEL(scrPrograma1_lblPararSalir, "Parar y Salir", LBL_PS_POSX, LBL_PS_POSY, LBL_PS_SIZEX, LBL_PS_SIZEY, FONT_BERLIN_SANS_FBDEMI12)

// Console estado
D4D_DECLARE_STD_CONSOLE(scrPrograma1_cnslEstado, CNSL_EST_POSX, CNSL_EST_POSY, CNSL_EST_SIZEX, CNSL_EST_SIZEY, CNSL_EST_LINE_CNT, CNSL_EST_CHAR_CNT, FONT_BERLIN_SANS_FBDEMI12_HIGH)


// Graph
Byte dataTrace[617];

D4D_DECLARE_STD_RGRAPH_BEGIN(scrPrograma1_graph, "ECG (Prueba)", GRAPH_POSX, GRAPH_POSY, GRAPH_SIZEX, GRAPH_SIZEY, 8, 4, 2, 20, FONT_ARIAL7, FONT_ARIAL7)
  D4D_DECLARE_GRAPH_TRACE(dataTrace, D4D_COLOR_RED, D4D_LINE_THICK, D4D_GRAPH_TRACE_TYPE_LINE)
D4D_DECLARE_GRAPH_END()

/*****************************************************************************
*
* eGUI/D4D screen declaration
*
*
*****************************************************************************/

// Standard screen declaration
D4D_DECLARE_STD_SCREEN_BEGIN(screen_programa1, ScreenPrograma1_)
	D4D_DECLARE_SCREEN_OBJECT(scrPrograma1_lblTitle)
	D4D_DECLARE_SCREEN_OBJECT(scrPrograma1_lblIniciarParar)
	D4D_DECLARE_SCREEN_OBJECT(scrPrograma1_lblPararSalir)
	D4D_DECLARE_SCREEN_OBJECT(scrPrograma1_cnslEstado)
	D4D_DECLARE_SCREEN_OBJECT(scrPrograma1_graph)
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
//ecg
Byte senial1[617]={100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
Byte* pDummyMusic1=senial1;



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
static void ScreenPrograma1_OnInit()
{
	D4D_CnslPutString(&scrPrograma1_cnslEstado, "Estado: inactivo.");
}

// Screen on Activate function called with each screen activation
static void ScreenPrograma1_OnActivate()
{

}

// Screen "Main" function called periodically in each D4D_poll runs
static void ScreenPrograma1_OnMain()
{
  if(iniciar)
  {
//	D4D_COOR dim;
    // each 100ms
    if(flag100ms)
    {
//      Byte tmp_output;

      flag100ms = 0;
       //add new data into "input audio signal" graph
      D4D_GraphAddTracesData(&scrPrograma1_graph, pDummyMusic1);
      pDummyMusic1 += 1;
      if(pDummyMusic1==&senial1[616])pDummyMusic1=&senial1[0];


    }
  }
}


// Screen on DeActivate function called with each screen deactivation
static void ScreenPrograma1_OnDeactivate()
{
	if(iniciar==D4D_TRUE){
		iniciar=D4D_FALSE;
		LedOff(LED_1);
		D4D_CnslClearAll(&scrPrograma1_cnslEstado);
		D4D_CnslPutString(&scrPrograma1_cnslEstado, "Estado: inactivo.");
	}
	D4D_GraphClearAll(&scrPrograma1_graph);
}

// Screen on message function called with each internal massage for this screen
static Byte ScreenPrograma1_OnObjectMsg(D4D_MESSAGE* pMsg)
{
  if(pMsg->nMsgId == D4D_MSG_KEYDOWN)
  	  {
  		  if(pMsg->prm.key == D4D_KEY_SCANCODE_ENTER)
  		  {
  			  if(iniciar==D4D_FALSE){
  				  iniciar=D4D_TRUE;
  				  LedOn(LED_1);
  				  D4D_CnslClearAll(&scrPrograma1_cnslEstado);
  				  D4D_CnslPutString(&scrPrograma1_cnslEstado, "Estado: Efectuando operacion.");
  				  MoverActuador(CONTACTO);

  			  }
  			  else{
  				  iniciar=D4D_FALSE;
  				  LedOff(LED_1);
  				  D4D_CnslClearAll(&scrPrograma1_cnslEstado);
  				  D4D_CnslPutString(&scrPrograma1_cnslEstado, "Estado: inactivo.");
  			  }
  		  }
  	  }
  return 0;
}




