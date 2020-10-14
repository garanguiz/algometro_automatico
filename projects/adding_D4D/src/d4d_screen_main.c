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
#include "../d4d/graphic_objects/d4d_menu.c"
#include "led.h"
#include "imagenes.h"
#include "../d4d/graphic_objects/d4d_picture.c"

//extern unsigned int flag100ms;


D4D_EXTERN_SCREEN(screen_homing)
//D4D_EXTERN_SCREEN(screen_programa1)


/*****************************************************************************
*
* Graphic objects coordination specifications
*
*
*****************************************************************************/

// Menu object - "Menu"

#define MENU_POSX	D4D_SCREEN_SIZE_LONGER_SIDE/4
#define MENU_POSY	D4D_SCREEN_SIZE_SHORTER_SIDE/4

#define MENU_SIZEX	D4D_SCREEN_SIZE_LONGER_SIDE/2
#define MENU_SIZEY	D4D_SCREEN_SIZE_SHORTER_SIDE/2


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
  D4D_DECLARE_MENU_ITEM_FULL("Homing", NULL, &screen_homing)
  D4D_DECLARE_MENU_ITEM("Programa 1", NULL)
  D4D_DECLARE_MENU_ITEM("Programa 2", NULL)
  D4D_DECLARE_MENU_ITEM("Programa 3", NULL)
D4D_DECLARE_MENU_END(scrWinMenu_menu)

//Logos
D4D_DECLARE_STD_PICTURE(scrMain_logo1, 0, D4D_SCREEN_SIZE_SHORTER_SIDE-70, 200, 65, &bmp_fiunerlogo)
D4D_DECLARE_STD_PICTURE(scrMain_logo2, D4D_SCREEN_SIZE_LONGER_SIDE-205, D4D_SCREEN_SIZE_SHORTER_SIDE-75, 200, 70, &bmp_prototipadologo)

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
static void ScrMain_OnClickMenu(D4D_OBJECT* pThis, D4D_MENU_INDEX ix)
{
	switch(ix){
	case 0:
		D4D_ActivateScreen(D4D_MenuGetItemUserData(pThis), D4D_FALSE);
		break;
	case 1:
		LedToggle(LED_1);
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

// One time called screen function in screen initialization proces
static void ScreenMain_OnInit()
{

  
}

// Screen on Activate function called with each screen activation
static void ScreenMain_OnActivate()
{
	D4D_CaptureKeys(&scrMain_menu);
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




