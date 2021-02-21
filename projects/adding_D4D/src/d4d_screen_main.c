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
* @author    Petr Gargulak, Gonzalo Aranguiz
* 
* @brief     D4D driver - main screen source file of eGUI/D4D demo application
*
* Pantalla principal, implementada a partir de plantilla de ejemplo de la librería gráfica.
* Consta de un menú con 4 opciones, de las cuales sólo está implementada la primera.
*
******************************************************************************/

#include "../d4d/d4d.h" //JB
#include "fonts.h" //JB
#include "../d4d/graphic_objects/d4d_menu.c"
#include "led.h"
#include "imagenes.h"
#include "../d4d/graphic_objects/d4d_picture.c"


D4D_EXTERN_SCREEN(screen_pruebappt) //Declara la nueva pantalla que se activará desde la actual.
//D4D_EXTERN_SCREEN(screen_programa1)


/*****************************************************************************
*
* Graphic objects coordination specifications
*
*
*****************************************************************************/
#define EDGE_SPACE	2

// Menu object - "Menu"

#define MENU_POSX	D4D_SCREEN_SIZE_LONGER_SIDE/4
#define MENU_POSY	D4D_SCREEN_SIZE_SHORTER_SIDE/4

#define MENU_SIZEX	D4D_SCREEN_SIZE_LONGER_SIDE/2
#define MENU_SIZEY	D4D_SCREEN_SIZE_SHORTER_SIDE/2

// Label object - Seleccionar

#define LBL_SEL_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/2 + EDGE_SPACE)
#define LBL_SEL_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-40-EDGE_SPACE)

#define LBL_SEL_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_SEL_SIZEY 40

// Label object - Subir

#define LBL_SU_POSX (EDGE_SPACE)
#define LBL_SU_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-40-EDGE_SPACE)

#define LBL_SU_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_SU_SIZEY 40

// Label object - Bajar

#define LBL_BA_POSX (D4D_SCREEN_SIZE_LONGER_SIDE/4 + EDGE_SPACE)
#define LBL_BA_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE-40-EDGE_SPACE)

#define LBL_BA_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE/4 - 2*EDGE_SPACE)
#define LBL_BA_SIZEY 40
/*****************************************************************************
*
* Graphic objects callback/events functions declaration
*
*
*****************************************************************************/
static void ScrMain_OnClickMenu(D4D_OBJECT* pThis, D4D_MENU_INDEX ix);


/*****************************************************************************
*
* Graphic object declarations
*
*
*****************************************************************************/
//Menu
D4D_DECLARE_STD_RMENU_BEGIN(scrMain_menu, "SELECCIONE OPERACION" , FONT_BERLIN_SANS_FBDEMI12_BIG, MENU_POSX, MENU_POSY, MENU_SIZEX, MENU_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12_BIG, FONT_BERLIN_SANS_FBDEMI12_BIG, NULL, ScrMain_OnClickMenu)
  D4D_DECLARE_MENU_ITEM_FULL("Prueba de PPT", NULL, &screen_pruebappt)
  D4D_DECLARE_MENU_ITEM("Programa 1", NULL) //No implementado
  D4D_DECLARE_MENU_ITEM("Programa 2", NULL) //No implementado
  D4D_DECLARE_MENU_ITEM("Programa 3", NULL) //No implementado
D4D_DECLARE_MENU_END(scrWinMenu_menu)

//Logos
D4D_DECLARE_STD_PICTURE(scrMain_logo1, 0, 0, 200, 65, &bmp_fiunerlogo)
D4D_DECLARE_STD_PICTURE(scrMain_logo2, D4D_SCREEN_SIZE_LONGER_SIDE-200, 0, 200, 70, &bmp_prototipadologo)

// Label Seleccionar
D4D_DECLARE_STD_RLABEL(scrMain_lblSeleccionar, "Seleccionar", LBL_SEL_POSX, LBL_SEL_POSY, LBL_SEL_SIZEX, LBL_SEL_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12)

// Label Subir
D4D_DECLARE_STD_RLABEL(scrMain_lblSubir, "Subir", LBL_SU_POSX, LBL_SU_POSY, LBL_SU_SIZEX, LBL_SU_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12)

// Label Bajar
D4D_DECLARE_STD_RLABEL(scrMain_lblBajar, "Bajar", LBL_BA_POSX, LBL_BA_POSY, LBL_BA_SIZEX, LBL_BA_SIZEY, 8, FONT_BERLIN_SANS_FBDEMI12)

/*****************************************************************************
*
* eGUI/D4D screen declaration
*
*
*****************************************************************************/

// Standard screen declaration
D4D_DECLARE_SCREEN_BEGIN(screen_main, ScreenMain_, 0, 0, D4D_SCREEN_SIZE_LONGER_SIDE, D4D_SCREEN_SIZE_SHORTER_SIDE, NULL, 0, NULL, (D4D_SCR_F_BCKG | D4D_SCR_F_TOUCHENABLE), NULL)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_menu)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_logo1)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_logo2)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_lblSeleccionar)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_lblSubir)
	D4D_DECLARE_SCREEN_OBJECT(scrMain_lblBajar)
D4D_DECLARE_SCREEN_END()    

/*****************************************************************************
*
* Local variables 
*
*
*****************************************************************************/




/*****************************************************************************
*
* Local function 
*
*
*****************************************************************************/
/**
 * @brief Función llamada al seleccionar una de las opciones del menú.
 * @param pThis Puntero al objeto relacionado con la opción seleccionada (pantalla a activar), indicado en la declaración del elemento de menú.
 * @param ix Índice de la opción seleccionada.
 */
static void ScrMain_OnClickMenu(D4D_OBJECT* pThis, D4D_MENU_INDEX ix)
{
	switch(ix){
	case 0:
		D4D_ActivateScreen(D4D_MenuGetItemUserData(pThis), D4D_FALSE);//Activa la pantalla de prueba PPT
		break;
	case 1:
		LedToggle(LED_1);//No activa ninguna pantalla, enciende un LED de la placa como prueba.
		break;
	case 2:
		LedToggle(LED_2);
		break;
	case 3:
		LedToggle(LED_3);
		break;
	}


}


/*****************************************************************************
*
* Screen system functions 
*
*
*****************************************************************************/

// One time called screen function in screen initialization process
static void ScreenMain_OnInit()
{

}

// Screen on Activate function called with each screen activation
static void ScreenMain_OnActivate()
{
	D4D_CaptureKeys(&scrMain_menu);//Indica que los eventos de las teclas están relacionados con el elemento menú.
}

// Screen "Main" function called periodically in each D4D_poll runs
static void ScreenMain_OnMain()
{


}

// Screen on DeActivate function called with each screen deactivation
static void ScreenMain_OnDeactivate()
{

}

// Screen on message function called with each internal massage for this screen
static Byte ScreenMain_OnObjectMsg(D4D_MESSAGE* pMsg)
{
  D4D_UNUSED(pMsg);
  
  return 0;
}




