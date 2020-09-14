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
#include "pictures.h"//JB
#include "../d4d/graphic_objects/d4d_graph.c"
#include "../d4d/graphic_objects/d4d_gauge.c"
#include "../d4d/graphic_objects/d4d_slider.c"
#include "../d4d/graphic_objects/d4d_button.c"
#include "../d4d/graphic_objects/d4d_label.c"
#include "../d4d/graphic_objects/d4d_check_box.c"

extern unsigned int flag100ms;


//D4D_EXTERN_SCREEN(screen_winmenu)


/*****************************************************************************
*
* Graphic objects coordination specifications
*
*
*****************************************************************************/


// Graph object "Input audio Signal"

//#define CENTER_SPACE	6
//#define EDGE_SPACE	2
//
//#define GRAPH_POSX EDGE_SPACE
//#define GRAPH_POSY 56
//
//#define GRAPH_SIZEX (D4D_SCREEN_SIZE_LONGER_SIDE - (2 * EDGE_SPACE) - CENTER_SPACE - LBL_VOL_SIZEX)
//#define GRAPH_SIZEY (D4D_SCREEN_SIZE_SHORTER_SIDE - (2 * EDGE_SPACE) - BTN_SIZEY - GRAPH_POSY)

//#define GRAPH_DATA_HISTORY 20

// Label object - "Estado"

#define LBL_EST_POSX 40
#define LBL_EST_POSY 430

#define LBL_EST_SIZEX 700
#define LBL_EST_SIZEY 40


// Label object - Freescale eGUI(D4D)

//#define LBL_TIT1_POSX GRAPH_POSX
//#define LBL_TIT1_POSY 35
//
//#define LBL_TIT1_SIZEX GRAPH_SIZEX
//#define LBL_TIT1_SIZEY 18


// Label object "Volume"

//#define LBL_VOL_POSX (GRAPH_POSX + GRAPH_SIZEX + CENTER_SPACE)
//#define LBL_VOL_POSY 2
//
//#define LBL_VOL_SIZEX 130
//#define LBL_VOL_SIZEY 20

// Slider object "Volume"

//#define SLDR_VOL_POSX LBL_VOL_POSX
//#define SLDR_VOL_POSY (LBL_VOL_POSY + LBL_VOL_SIZEY + EDGE_SPACE)
//
//#define SLDR_VOL_SIZEX LBL_VOL_SIZEX
//#define SLDR_VOL_SIZEY 30

// Label object "Balance"

//#define LBL_BAL_POSX LBL_VOL_POSX
//#define LBL_BAL_POSY (SLDR_VOL_POSY + SLDR_VOL_SIZEY + 5)
//
//#define LBL_BAL_SIZEX LBL_VOL_SIZEX
//#define LBL_BAL_SIZEY LBL_VOL_SIZEY

// Slider object "Balance"

//#define SLDR_BAL_POSX SLDR_VOL_POSX
//#define SLDR_BAL_POSY (LBL_BAL_POSY + LBL_BAL_SIZEY + 2)
//
//#define SLDR_BAL_SIZEX LBL_BAL_SIZEX
//#define SLDR_BAL_SIZEY SLDR_VOL_SIZEY

// Gauge objects "Output audio Signal"

//#define GAUGE_SIZEX 64
//#define GAUGE_SIZEY GAUGE_SIZEX
//
//#define GAUGE_POSX SLDR_VOL_POSX
//#define GAUGE_POSY (SLDR_BAL_POSY + SLDR_BAL_SIZEY + 4)
//
//#define GAUGES_POSX(x) (GAUGE_POSX + (GAUGE_SIZEX * (x)))
//#define GAUGES_POSY GAUGE_POSY

// Check box objects

#define CHECKB_POSX 50
#define CHECKB_HOM_POSY 50
#define CHECKB_PROG1_POSY 150
#define CHECKB_PROG2_POSY 250
#define CHECKB_PROG3_POSY 350

#define CHECKB_SIZE_X 300
#define CHECKB_SIZE_Y 50

// Button objects "Iniciar/Parar"

#define BTN_INI_SIZEX 100
#define BTN_INI_SIZEY 100

#define BTN_INI_POSX 400
#define BTN_INI_POSY 180

#define BTN_PAR_SIZEX 200
#define BTN_PAR_SIZEY 360

#define BTN_PAR_POSX 550
#define BTN_PAR_POSY 50

// Icon object "animation of equalizer"

//#define ICON_EQU_POSX (D4D_SCREEN_SIZE_LONGER_SIDE - 2 - ICON_EQU_SIZEX)
//#define ICON_EQU_POSY (D4D_SCREEN_SIZE_SHORTER_SIDE - 2 - ICON_EQU_SIZEY)
//
//#define ICON_EQU_SIZEX 50
//#define ICON_EQU_SIZEY 35

/*****************************************************************************
*
* Graphic objects callback/events functions declaration
*
*
*****************************************************************************/

static void ScrMain_OnClickBtnIniciar(D4D_OBJECT* pThis);
static void ScrMain_OnClickBtnParar(D4D_OBJECT* pThis);
//static void ScrMain_OnClickBtnStop(D4D_OBJECT* pThis);
static void ScrMain_OnChangeCheckBHoming(D4D_OBJECT* pThis);
static void ScrMain_OnChangeCheckBProg1(D4D_OBJECT* pThis);
static void ScrMain_OnChangeCheckBProg2(D4D_OBJECT* pThis);
static void ScrMain_OnChangeCheckBProg3(D4D_OBJECT* pThis);
//static void ScrMain_OnChangeSldr(D4D_OBJECT* pThis);


/*****************************************************************************
*
* Graphic object declarations
*
*
*****************************************************************************/

// Gauges
//D4D_DECLARE_STD_RGAUGE(scrMain_gaugeLeft, "L", GAUGES_POSX(0), GAUGES_POSY, GAUGE_SIZEX-2, GAUGE_SIZEY-2, 8, 3, 3, GAUGE_SIZEX - 12, GAUGE_SIZEY - 12, GAUGE_SIZEX - 25, &bmpGauge, FONT_ARIAL7_WIDE, NULL)
//D4D_DECLARE_STD_RGAUGE(scrMain_gaugeRight, "R", GAUGES_POSX(1), GAUGES_POSY, GAUGE_SIZEX-2, GAUGE_SIZEY-2, 8, 3, 3, GAUGE_SIZEX - 12, GAUGE_SIZEY - 12, GAUGE_SIZEX - 25, &bmpGauge, FONT_ARIAL7_WIDE, NULL)

// Check Boxes
D4D_DECLARE_STD_CHECKBOX(scrMain_checkBxHoming, "Homing", CHECKB_POSX, CHECKB_HOM_POSY, CHECKB_SIZE_X, CHECKB_SIZE_Y, NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnChangeCheckBHoming)
D4D_DECLARE_STD_CHECKBOX(scrMain_checkBxProg1, "Programa 1", CHECKB_POSX, CHECKB_PROG1_POSY, CHECKB_SIZE_X, CHECKB_SIZE_Y, NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnChangeCheckBProg1)
D4D_DECLARE_STD_CHECKBOX(scrMain_checkBxProg2, "Programa 2", CHECKB_POSX, CHECKB_PROG2_POSY, CHECKB_SIZE_X, CHECKB_SIZE_Y, NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnChangeCheckBProg2)
D4D_DECLARE_STD_CHECKBOX(scrMain_checkBxProg3, "Programa 3", CHECKB_POSX, CHECKB_PROG3_POSY, CHECKB_SIZE_X, CHECKB_SIZE_Y, NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnChangeCheckBProg3)


// Label
//D4D_DECLARE_STD_LABEL(scrMain_lblVol, "Volume", LBL_VOL_POSX, LBL_VOL_POSY, LBL_VOL_SIZEX, LBL_VOL_SIZEY, FONT_BERLIN_SANS_FBDEMI12)
//// Slider
//static D4D_TCHAR scrMain_sldrVol_str[] = " 0";
//D4D_DECLARE_RSLIDER_AUTOSIZE(scrMain_sldrVol, scrMain_sldrVol_str, SLDR_VOL_POSX, SLDR_VOL_POSY, SLDR_VOL_SIZEX, SLDR_VOL_SIZEY, 8, (D4D_SLDR_F_DEFAULT | D4D_SLDR_F_AUTOCOLOR | D4D_SLDR_F_BAR_SCALECOLOR), NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, NULL, ScrMain_OnChangeSldr, NULL)
//// Label
//D4D_DECLARE_STD_LABEL(scrMain_lblBal, "Balance", LBL_BAL_POSX, LBL_BAL_POSY, LBL_BAL_SIZEX, LBL_BAL_SIZEY, FONT_BERLIN_SANS_FBDEMI12)
//// Slider
//static D4D_TCHAR scrMain_sldrBalance_str[] = " 0 ";
//D4D_DECLARE_RSLIDER_AUTOSIZE(scrMain_sldrBalance, scrMain_sldrBalance_str, SLDR_BAL_POSX, SLDR_BAL_POSY, SLDR_BAL_SIZEX, SLDR_BAL_SIZEY, 8, (D4D_SLDR_F_DEFAULT | D4D_SLDR_F_AUTOCOLOR | D4D_SLDR_F_BAR_SCALECOLOR), NULL, NULL, FONT_BERLIN_SANS_FBDEMI12, NULL, ScrMain_OnChangeSldr, NULL)



// Graph
//Byte dataTraceLeft[617];
//Byte dataTraceRight[GRAPH_DATA_HISTORY];
//
//D4D_DECLARE_STD_RGRAPH_BEGIN(scrMain_graph, "Input Audio Signal", GRAPH_POSX, GRAPH_POSY, GRAPH_SIZEX, GRAPH_SIZEY, 8, 4, 2, 20, FONT_ARIAL7, FONT_ARIAL7)
//  D4D_DECLARE_GRAPH_TRACE(dataTraceLeft, D4D_COLOR_RED, D4D_LINE_THICK, D4D_GRAPH_TRACE_TYPE_LINE)
// // D4D_DECLARE_GRAPH_TRACE(dataTraceRight, D4D_COLOR_GREEN, D4D_LINE_THIN, D4D_GRAPH_TRACE_TYPE_LINE)
//D4D_DECLARE_GRAPH_END()

// Buttons
//D4D_DECLARE_TXT_RBUTTON(scrMain_btnPlay, "Play", BTN_POSX(0), BTN_POSY, BTN_SIZEX, BTN_SIZEY, BTN_RADIUS, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnPlay)
//D4D_DECLARE_TXT_RBUTTON(scrMain_btnStop, "Stop", BTN_POSX(1), BTN_POSY, BTN_SIZEX, BTN_SIZEY, BTN_RADIUS, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnStop)
//D4D_DECLARE_TXT_BUTTON(scrMain_btnMenu, "Menu", BTN_POSX(2), BTN_POSY, BTN_SIZEX, BTN_SIZEY, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnMenu)
D4D_DECLARE_TXT_BUTTON(scrMain_btnIniciar, "Iniciar", BTN_INI_POSX, BTN_INI_POSY, BTN_INI_SIZEX, BTN_INI_SIZEY, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnIniciar)
D4D_DECLARE_TXT_BUTTON(scrMain_btnParar, "Parar", BTN_PAR_POSX, BTN_PAR_POSY, BTN_PAR_SIZEX, BTN_PAR_SIZEY, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnParar)
//D4D_DECLARE_TXT_BUTTON(scrMain_btnMenu, "Limpiar", 210, 460, BTN_SIZEX, BTN_SIZEY, FONT_BERLIN_SANS_FBDEMI12, ScrMain_OnClickBtnMenu)

// Label Estado
D4D_DECLARE_STD_LABEL(scrMain_lblEstado, "Estado:", LBL_EST_POSX, LBL_EST_POSY, LBL_EST_SIZEX, LBL_EST_SIZEY, FONT_BERLIN_SANS_FBDEMI12_HIGH)
//D4D_DECLARE_STD_LABEL(scrMain_lblTitle1, "Where the biomedical dreams come true...", LBL_TIT1_POSX, LBL_TIT1_POSY, LBL_TIT1_SIZEX, LBL_TIT1_SIZEY, FONT_ARIAL7)


//// Icon
//D4D_DECLARE_STD_ICON_BEGIN(scrMain_icnAnimEqu, NULL, ICON_EQU_POSX, ICON_EQU_POSY, 50, 35, 0, 0, FONT_ARIAL7, NULL)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu1)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu2)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu3)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu4)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu5)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu6)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu7)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu8)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu9)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu10)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu11)
//  D4D_DECLARE_ICON_BMP(&bmpAnimEqu12)
//D4D_DECLARE_ICON_END()

// declare FSL logo picture
//D4D_DECLARE_STD_PICTURE(scrMain_picFsl, BTN_POSX(3), BTN_POSY, 24, 24, &bmpFreescale)


/*****************************************************************************
*
* eGUI/D4D screen declaration
*
*
*****************************************************************************/

// Standard screen declaration
D4D_DECLARE_SCREEN_BEGIN(screen_main, ScreenMain_, 0, 0, D4D_SCREEN_SIZE_LONGER_SIDE, D4D_SCREEN_SIZE_SHORTER_SIDE, NULL, 0, NULL, (D4D_SCR_F_BCKG | D4D_SCR_F_TOUCHENABLE), NULL)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_lblEstado)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_lblTitle1)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_graph)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_lblVol)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_sldrVol)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_lblBal)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_sldrBalance)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_gaugeLeft)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_gaugeRight)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_checkBxHoming)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_checkBxProg1)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_checkBxProg2)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_checkBxProg3)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_btnIniciar)
  D4D_DECLARE_SCREEN_OBJECT(scrMain_btnParar)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_picFsl)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_icnAnimEqu)
//  D4D_DECLARE_SCREEN_OBJECT(scrMain_btnMenu)
D4D_DECLARE_SCREEN_END()    

/*****************************************************************************
*
* Local variables 
*
*
*****************************************************************************/

//static int musicEnable = D4D_TRUE;
//Byte valor=0;
//Byte sube_1_baja_0=1;
//LWord indice=0;
////Byte senial[617]={40,41,42,43,44,45,46,47,47,48,49,50,51,52,53,54,54,55,56,57,58,58,59,60,61,61,62,63,63,64,64,65,65,66,66,67,67,68,68,68,69,69,69,69,69,70,70,70,70,70,70,70,70,70,70,70,69,69,69,69,69,68,68,68,67,67,66,66,65,65,64,64,63,63,62,61,61,60,59,58,58,57,56,55,54,54,53,52,51,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,33,32,31,30,29,28,27,26,26,25,24,23,22,22,21,20,19,19,18,17,17,16,16,15,15,14,14,13,13,12,12,12,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12,13,13,14,14,15,15,16,16,17,17,18,19,19,20,21,22,22,23,24,25,26,26,27,28,29,30,31,32,33,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,47,48,49,50,51,52,53,54,54,55,56,57,58,58,59,60,61,61,62,63,63,64,64,65,65,66,66,67,67,68,68,68,69,69,69,69,69,70,70,70,70,70,70,70,70,70,70,70,69,69,69,69,69,68,68,68,67,67,66,66,65,65,64,64,63,63,62,61,61,60,59,58,58,57,56,55,54,54,53,52,51,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,33,32,31,30,29,28,27,26,26,25,24,23,22,22,21,20,19,19,18,17,17,16,16,15,15,14,14,13,13,12,12,12,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12,13,13,14,14,15,15,16,16,17,17,18,19,19,20,21,22,22,23,24,25,26,26,27,28,29,30,31,32,33,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,47,48,49,50,51,52,53,54,54,55,56,57,58,58,59,60,61,61,62,63,63,64,64,65,65,66,66,67,67,68,68,68,69,69,69,69,69,70,70,70,70,70,70,70,70,70,70,70,69,69,69,69,69,68,68,68,67,67,66,66,65,65,64,64,63,63,62,61,61,60,59,58,58,57,56,55,54,54,53,52,51,50,49,48,47,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,33,32,31,30,29,28,27,26,26,25,24,23,22,22,21,20,19,19,18,17,17,16,16,15,15,14,14,13,13,12,12,12,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,12,12,12,13,13,14,14,15,15,16,16,17,17,18,19,19,20,21,22,22,23,24,25,26,26,27,28,29,30,31,32,33,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,47,48,49,50,51,52,53,54,54};
////Byte senial[617]={125,129,133,137,141,145,148,152,156,160,164,167,171,175,178,182,185,189,192,195,198,202,205,208,211,213,216,219,221,224,226,228,231,233,235,236,238,240,241,243,244,245,246,247,248,248,249,249,250,250,250,250,250,249,249,248,248,247,246,245,244,243,241,240,238,236,235,233,231,228,226,224,221,219,216,213,211,208,205,202,198,195,192,189,185,182,178,175,171,167,164,160,156,152,148,145,141,137,133,129,125,121,117,113,109,105,102,98,94,90,86,83,79,75,72,68,65,61,58,55,52,48,45,42,39,37,34,31,29,26,24,22,19,17,15,14,12,10,9,7,6,5,4,3,2,2,1,1,0,0,0,0,0,1,1,2,2,3,4,5,6,7,9,10,12,14,15,17,19,22,24,26,29,31,34,37,39,42,45,48,52,55,58,61,65,68,72,75,79,83,86,90,94,98,102,105,109,113,117,121,125,129,133,137,141,145,148,152,156,160,164,167,171,175,178,182,185,189,192,195,198,202,205,208,211,213,216,219,221,224,226,228,231,233,235,236,238,240,241,243,244,245,246,247,248,248,249,249,250,250,250,250,250,249,249,248,248,247,246,245,244,243,241,240,238,236,235,233,231,228,226,224,221,219,216,213,211,208,205,202,198,195,192,189,185,182,178,175,171,167,164,160,156,152,148,145,141,137,133,129,125,121,117,113,109,105,102,98,94,90,86,83,79,75,72,68,65,61,58,55,52,48,45,42,39,37,34,31,29,26,24,22,19,17,15,14,12,10,9,7,6,5,4,3,2,2,1,1,0,0,0,0,0,1,1,2,2,3,4,5,6,7,9,10,12,14,15,17,19,22,24,26,29,31,34,37,39,42,45,48,52,55,58,61,65,68,72,75,79,83,86,90,94,98,102,105,109,113,117,121,125,129,133,137,141,145,148,152,156,160,164,167,171,175,178,182,185,189,192,195,198,202,205,208,211,213,216,219,221,224,226,228,231,233,235,236,238,240,241,243,244,245,246,247,248,248,249,249,250,250,250,250,250,249,249,248,248,247,246,245,244,243,241,240,238,236,235,233,231,228,226,224,221,219,216,213,211,208,205,202,198,195,192,189,185,182,178,175,171,167,164,160,156,152,148,145,141,137,133,129,125,121,117,113,109,105,102,98,94,90,86,83,79,75,72,68,65,61,58,55,52,48,45,42,39,37,34,31,29,26,24,22,19,17,15,14,12,10,9,7,6,5,4,3,2,2,1,1,0,0,0,0,0,1,1,2,2,3,4,5,6,7,9,10,12,14,15,17,19,22,24,26,29,31,34,37,39,42,45,48,52,55,58,61,65,68,72,75,79,83,86,90,94,98,102,105,109,113,117,121,125,129,133,137,141,145,148,152,156,160,164,167,171,175,178,182,185};
////ecg
//Byte senial[617]={100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,102,106,109,113,117,120,124,128,131,133,129,126,122,119,115,111,108,104,101,101,101,101,101,100,100,100,100,100,100,100,92,82,71,92,112,133,154,174,195,178,149,119,90,60,31,31,60,89,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,103,105,107,109,110,112,114,116,117,116,115,113,111,109,108,106,104,102,101,101,101,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
//Byte* pDummyMusic=senial;



/*****************************************************************************
*
* Local function 
*
*
*****************************************************************************/

//Button Play OnClick CallBack
static void ScrMain_OnClickBtnIniciar(D4D_OBJECT* pThis)
{
	//musicEnable = D4D_TRUE;
//  D4D_IconAnimationStart(&scrMain_icnAnimEqu);
//  Log_AddObjectEvent(pThis, "Play click.");
}

//Button Stop OnClick CallBack
static void ScrMain_OnClickBtnParar(D4D_OBJECT* pThis)
{
//  musicEnable = D4D_FALSE;
//  D4D_IconAnimationStop(&scrMain_icnAnimEqu);
//  pDummyMusic = 0;
//  D4D_GraphClearAll(&scrMain_graph);
//  Log_AddObjectEvent(pThis, "Stop click.");
}

//Button Menu OnClick CallBack
//static void ScrMain_OnClickBtnMenu(D4D_OBJECT* pThis)
//{
////  D4D_ActivateScreen(&screen_winmenu, D4D_FALSE);
////  Log_AddObjectEvent(pThis, "Menu click.");
//	D4D_GraphClearAll(&scrMain_graph);
//}

//Slider OnChange CallBack
//static void ScrMain_OnChangeSldr(D4D_OBJECT* pThis)
//{
////  D4D_TCHAR tmp_txt[4];
////  tmp_txt[D4D_SprintDecS8(D4D_SldrGetValue(pThis), &tmp_txt[0], 0)] = 0;
////  D4D_SldrSetText(pThis, tmp_txt);
////
////  if(pThis == &scrMain_sldrBalance)
////  {
////    Log_AddObjectEvent(pThis, "Balance Changed.");
////  }
////  else
////  {
////    Log_AddObjectEvent(pThis, "Volume Changed.");
////  }
//}

//CheckBox Left OnChange CallBack
static void ScrMain_OnChangeCheckBHoming(D4D_OBJECT* pThis)
{
////  if(!D4D_CheckBoxGetValue(pThis))
////    D4D_GaugSetValue(&scrMain_gaugeLeft, 0);
////  Log_AddObjectEvent(pThis, "Left output changed.");
}
//
////CheckBox Right OnChange CallBack
static void ScrMain_OnChangeCheckBProg1(D4D_OBJECT* pThis)
{
////  if(!D4D_CheckBoxGetValue(pThis))
////    D4D_GaugSetValue(&scrMain_gaugeRight, 0);
////  Log_AddObjectEvent(pThis, "Right output changed.");
}

static void ScrMain_OnChangeCheckBProg2(D4D_OBJECT* pThis)
{

}

static void ScrMain_OnChangeCheckBProg3(D4D_OBJECT* pThis)
{

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
  D4D_TEXT_PROPERTIES tmp_txtProperties;
//  D4D_SLIDER_LIMITS tmp_limits = { -16, 16, 1 , 0};
//  D4D_GAUGE_LIMITS tmp_glimits = { 0, 127, 0, 63};

  // Gauges initialization
//  D4D_GaugSetLimits(&scrMain_gaugeLeft, &tmp_glimits);
//  D4D_GaugSetLimits(&scrMain_gaugeRight, &tmp_glimits);
//
  // Balance slider initialization
//  D4D_SldrSetLimits(&scrMain_sldrBalance, &tmp_limits);
  
  // Volume slider initialization
//  tmp_limits.valueMax = 32;
//  tmp_limits.valueMin = 0;
//  tmp_limits.step = 1;
//  D4D_SldrSetLimits(&scrMain_sldrVol, &tmp_limits);

  // Volume slider value initialization
//  D4D_SldrSetValue(&scrMain_sldrVol, 24);

  // Labels text propeties initialization
  tmp_txtProperties = D4D_ALIGN_H_LEFT_MASK | D4D_ALIGN_V_CENTER_MASK;
//
//  D4D_SetTextProperties(&scrMain_lblVol, tmp_txtProperties);
//  D4D_SetTextProperties(&scrMain_lblBal, tmp_txtProperties);
  D4D_SetTextProperties(&scrMain_lblEstado, tmp_txtProperties);
//  D4D_SetTextProperties(&scrMain_lblTitle1, tmp_txtProperties);
  
  // Check boxes initialization
//  D4D_CheckBoxSetValue(&scrMain_checkBxLeft, D4D_TRUE);
//  D4D_CheckBoxSetValue(&scrMain_checkBxRight, D4D_TRUE);
  
//  D4D_IconAnimationSetCounts(&scrMain_icnAnimEqu, 4);
//  D4D_IconAnimationStart(&scrMain_icnAnimEqu);
  
//  Log_AddScreenEvent("Main", "OnInit");
  
}

// Screen on Activate function called with each screen activation
static void ScreenMain_OnActivate()
{
//  pDummyMusic = 0;
//  Log_AddScreenEvent("Main", "OnActivate");
}

// Screen "Main" function called periodically in each D4D_poll runs
static void ScreenMain_OnMain()
{
//	D4D_COOR dim;
//  // if music is enabled
//  if(musicEnable)
//  {
//    // each 100ms
//    if(flag100ms)
//    {
//      Byte tmp_output;
//
//      flag100ms = 0;
//       //add new data into "input audio signal" graph
//      D4D_GraphAddTracesData(&scrMain_graph, pDummyMusic);
////      D4D_GraphAddTraceData(&scrMain_graph,(D4D_INDEX)indice,(D4D_GRAPH_VALUE) valor);
//
//      indice++;
//      valor=valor + sube_1_baja_0 - (1-sube_1_baja_0);
//      if(indice==616) indice=0;
//      if(valor==255)
//      {
//    	  sube_1_baja_0=0;
//      }
//      if(valor==0)
//      {
//    	  sube_1_baja_0=1;
//      }
//
//      dim=D4D_GraphGetSizeX(&scrMain_graph);
//
////      // if left output signal is enable (check the check box)
////      if(D4D_CheckBoxGetValue(&scrMain_checkBxLeft))
////      {
//        // modify the input signal to fit to the gauge
//        //tmp_output = (Byte)(255 - pDummyMusic[0]);
//
//        //tmp_output /= 2;
//
//        // Compute with volume of signal
//        tmp_output = D4D_MulDivUU8(tmp_output, (Byte)(D4D_SldrGetValue(&scrMain_sldrVol)), 32);
//
//        // Compute with balance of signal
//        if(D4D_SldrGetValue(&scrMain_sldrBalance) > 0)
//          tmp_output = D4D_MulDivUU8(tmp_output, (Byte)(17 - D4D_SldrGetValue(&scrMain_sldrBalance)), 16);
//
//
//        D4D_GaugSetValue(&scrMain_gaugeLeft, (D4D_GAUGE_VALUE)(tmp_output));
////      }
//
////      // if left output signal is enable (check the check box)
////      if(D4D_CheckBoxGetValue(&scrMain_checkBxRight))
////      {
////        // modify the input signal to fit to the gauge
////        tmp_output = (Byte)(255 - pDummyMusic[1]);
////
////        tmp_output /= 2;
////
////        // Compute with volume of signa
////        tmp_output = D4D_MulDivUU8(tmp_output, (Byte)(D4D_SldrGetValue(&scrMain_sldrVol)), 32);
////
////        // Compute with balance of signal
////        if(D4D_SldrGetValue(&scrMain_sldrBalance) < 0)
////          tmp_output = D4D_MulDivUU8(tmp_output, (Byte)(17 + D4D_SldrGetValue(&scrMain_sldrBalance)), 16);
////
////
////        D4D_GaugSetValue(&scrMain_gaugeRight, (D4D_GAUGE_VALUE)(tmp_output));
////      }
//
//      // update pointer to dummy data in memory of MCU
//        pDummyMusic += 1;
//        if(pDummyMusic==&senial[616])pDummyMusic=&senial[0];


//    }
//  }
}


// Screen on DeActivate function called with each screen deactivation
static void ScreenMain_OnDeactivate()
{
//  Log_AddScreenEvent("Main", "OnDeActivate");
}

// Screen on message function called with each internal massage for this screen
static Byte ScreenMain_OnObjectMsg(D4D_MESSAGE* pMsg)
{
  D4D_UNUSED(pMsg);
  
  return 0;
}




