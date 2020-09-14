/*
 * SSD1963.h
 *
 *  Created on: 29/7/2016
 *      Author: alumno
 */

/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  Solomon Systech. SSD1963 LCD controller driver
 *****************************************************************************
 * FileName:        SSD1963.h
 * Dependencies:    p24Fxxxx.h or plib.h
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:			TechToys Company
 * Remarks:			The origin of this file was the ssd1926.c driver released
 *					by Microchip Technology Incorporated.
 *
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright ?2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS?WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Anton Alkhimenok     08/27/08
 *****************************************************************************/

/*
******************************************************************************
* Versions 120709
*
* John Leung @ TechToys Co.			12/07/09
* www.TechToys.com.hk
******************************************************************************
*/

/*
******************************************************************************
* Remarks:
* 1. Removed hardware definition for LED_LAT_BIT and LED_TRIS_BIT
*	  because PWM pin of SSD1963 applied, therefore backlight intensity
*	  set by software
* 2. Add new function void SetBacklight(BYTE intensity)
* 3. Funny finding, PLL to 120MHz work only when 10MHz crystal applied with
* 	  multiplier N = 35. A crystal with 4MHz attempted but the PLL frequency
*	  failed to boost to 120MHz somehow!
*
* John Leung @ TechToys Co.			09/09/2009
* www.TechToys.com.hk
******************************************************************************
*/

/*
******************************************************************************
* Remarks:
* Port ot Microchip Graphics Library v2.00
* (1) Only BLOCKING CONFIGURATION is supported
* (2) GetPixel() not working yet.
* John Leung @ TechToys Co.			15th Jan 2010
* www.TechToys.com.hk
*
*/


#ifndef INC_SSD1963_H_
#define INC_SSD1963_H_


//include the command table for SSD1963
//#include "SSD1963_CMD.h"
#include "lpc_types.h"
#include "chip.h"


//include the SSD1963 API
//#include "SSD1963_api.h"
//#include "SSD1963_GUI.h"
//#include "SSD1963_gradient.h"
//#include "SSD1963_touch.h"

#include <stdbool.h>

//#define LCD_LONG_WIRE 1

/* LCD Panel settings */


#define DISP_HOR_RESOLUTION 800
#define DISP_VER_RESOLUTION 480

//#define DISP_ORIENTATION 90
#define DISP_ORIENTATION 0


//#define DISPLAY_MODE_8 1
//#define DISPLAY_MODE_16 1
#define DISPLAY_MODE_16_565 1

#define HDP (DISP_HOR_RESOLUTION-1)
//#define HDP 319


#define HT 928
#define HPS 46
#define LPS 15
#define HPW 48

#define VDP (DISP_VER_RESOLUTION-1)
//#define VDP 239

#define VT 525
#define VPS 16
#define FPS 8
#define VPW 16


#define LCD1_CS_PIN		GPIO_Pin_7	// PD7 NE1

extern uint16_t LCD1_Current_CS_Pin;
extern uint16_t LCD2_Current_CS_Pin;


/*********************************************************************
* Overview: Clipping region control codes to be used with SetClip(...)
*           function.
*********************************************************************/
#define CLIP_DISABLE       0 	// Disables clipping.
#define CLIP_ENABLE        1	// Enables clipping.


/*********************************************************************
* Macros: RGB565CONVERT(red, green, blue)
*
* Overview: Converts true color into 5:6:5 RGB format.
*
* PreCondition: none
*
* Input: Red, Green, Blue components.
*
* Output: 5 bits red, 6 bits green, 5 bits blue color.
*
* Side Effects: none
*
********************************************************************/
    #define RGB565CONVERT(red, green, blue) (uint16_t) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))


/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
#define BLACK               RGB565CONVERT(0,    0,      0)
#define BRIGHTBLUE          RGB565CONVERT(0,    0,      255)
#define BRIGHTGREEN         RGB565CONVERT(0,    255,    0)
#define BRIGHTCYAN          RGB565CONVERT(0,    255,    255)
#define BRIGHTRED           RGB565CONVERT(255,  0,      0)
#define BRIGHTMAGENTA       RGB565CONVERT(255,  0,      255)
#define BRIGHTYELLOW        RGB565CONVERT(255,  255,    0)
#define BLUE                RGB565CONVERT(0,    0,      128)
#define GREEN               RGB565CONVERT(0,    128,    0)
#define CYAN                RGB565CONVERT(0,    128,    128)
#define RED                 RGB565CONVERT(128,  0,      0)
#define MAGENTA             RGB565CONVERT(128,  0,      128)
#define BROWN               RGB565CONVERT(255,  128,    0)
#define LIGHTGRAY           RGB565CONVERT(180,  180,    180)
#define GRAY                RGB565CONVERT(140,  140,    140)
#define DARKGRAY            RGB565CONVERT(80,   80,     80)
#define LIGHTBLUE           RGB565CONVERT(128,  128,    255)
#define LIGHTGREEN          RGB565CONVERT(128,  255,    128)
#define LIGHTCYAN           RGB565CONVERT(128,  255,    255)
#define LIGHTRED            RGB565CONVERT(255,  128,    128)
#define LIGHTMAGENTA        RGB565CONVERT(255,  128,    255)
#define YELLOW              RGB565CONVERT(255,  255,    128)
#define WHITE               RGB565CONVERT(255,  255,    255)

/**
  * @brief  LCD color
  */
#define LCD_COLOR_WHITE          0xFFF0
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_GREY           0xF7DE
#define LCD_COLOR_BLUE           0x001F
#define LCD_COLOR_BLUE2          0x051F
#define LCD_COLOR_RED            0xF800
#define LCD_COLOR_MAGENTA        0xF81F
#define LCD_COLOR_GREEN          0x07E0
#define LCD_COLOR_CYAN           0x7FFF
#define LCD_COLOR_YELLOW         0xFFE0

#define GRAY0       	    RGB565CONVERT(224,  224,    224)
#define GRAY1         	    RGB565CONVERT(192,  192,    192)
#define GRAY2               RGB565CONVERT(160,  160,    160)
#define GRAY3               RGB565CONVERT(128,  128,    128)
#define GRAY4               RGB565CONVERT(96,   96,     96)
#define GRAY5               RGB565CONVERT(64,   64,     64)
#define GRAY6	            RGB565CONVERT(32,   32,     32)

/*********************************************************************
* Overview: Hardware definitions
*********************************************************************/

#define Lcd_Light_PORT 		2
#define Lcd_Light_PIN 		0

#define CS_PORT				2
#define CS_PIN 				5

#define RS_PORT 			2 //REGISTER SELECT: RS = 1 —–> Data Register RS = 0 —–> Command Code Register | D/C -> 1/0
#define RS_PIN 				1


#define WR_PORT				2
#define WR_PIN 				2

#define RD_PORT				2
#define RD_PIN 				3

#define RST_PORT 			2
#define RST_PIN 			6

#define UD_PORT 			2
#define UD_PIN 				8

#define RL_PORT 			2
#define RL_PIN 			    7

#define CS_HIGH 		 Chip_GPIO_SetPinState(LPC_GPIO, CS_PORT, CS_PIN, true);
#define CS_LOW 			 Chip_GPIO_SetPinState(LPC_GPIO, CS_PORT, CS_PIN, false);

#define RS_HIGH			Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, true);
#define RS_LOW  		Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, false);

#define WR_HIGH 		Chip_GPIO_SetPinState(LPC_GPIO, WR_PORT, WR_PIN, true);
#define WR_LOW 			Chip_GPIO_SetPinState(LPC_GPIO, WR_PORT, WR_PIN, false);

#define RD_HIGH			Chip_GPIO_SetPinState(LPC_GPIO, RD_PORT, RD_PIN, true);
#define RD_LOW 			Chip_GPIO_SetPinState(LPC_GPIO, RD_PORT, RD_PIN, false);

#define RST_HIGH 		Chip_GPIO_SetPinState(LPC_GPIO, RST_PORT, RST_PIN, true);
#define RST_LOW 		Chip_GPIO_SetPinState(LPC_GPIO, RST_PORT, RST_PIN, false);

#define Lcd_Light_ON   	Chip_GPIO_SetPinState(LPC_GPIO, Lcd_Light_PORT, Lcd_Light_PIN, true);
#define Lcd_Light_OFF  	Chip_GPIO_SetPinState(LPC_GPIO, Lcd_Light_PORT, Lcd_Light_PIN, false);

#define DATA_PORT		0
#define BIT0			2
#define BIT1 			3
#define BIT2			4
#define BIT3			5
#define BIT4			6
#define BIT5			7
#define BIT6			8
#define BIT7			9
#define BIT8			10
#define BIT9			11
#define BIT10			15
#define BIT11			16
#define BIT12			17
#define BIT13			18
#define BIT14			21
#define BIT15			22


/*********************************************************************
* Overview: Clipping region control and border settings.
*********************************************************************/
// Clipping region enable control
extern uint16_t _clipRgn;

// Left clipping region border
extern uint16_t _clipLeft;
// Top clipping region border
extern uint16_t _clipTop;
// Right clipping region border
extern uint16_t _clipRight;
// Bottom clipping region border
extern uint16_t _clipBottom;


// Active and Visual Pages
extern uint8_t _activePage;
extern uint8_t	_visualPage;


/*----- Low layer function -----*/
void LCD_EnableDisplayControl(void);
void LCD_CtrlLinesConfig(void);
void LCD_FSMCConfig(void);
void LCD_Init(void);

void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteIndex(uint16_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
inline void LCD_WriteRAM_Inline(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);

void LCD_WriteData(uint16_t data);
void LCD_WriteCommand(uint16_t cmd);
uint16_t LCD_readData(void);

/*********************************************************************
* Function:  void ResetDevice()
*
* Overview: Initializes LCD module.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void LCD_ResetDevice(void);

/*********************************************************************
* Macros:  GetMaxX()
*
* Overview: Returns maximum horizontal coordinate for visual display
*
* PreCondition: none
*
* Input: none
*
* Output: Maximum horizontal coordinates.
*
* Side Effects: none
*
* Note:
********************************************************************/
#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)

#define	GetMaxX() 			(DISP_VER_RESOLUTION-1)


#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)

#define	GetMaxX() 			(DISP_HOR_RESOLUTION-1)

#endif

/*********************************************************************
* Macros:  GetMaxY()
*
* Overview: Returns maximum vertical coordinate for visual display
*
* PreCondition: none
*
* Input: none
*
* Output: Maximum vertical coordinates.
*
* Side Effects: none
*
* Note:
********************************************************************/
#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)

#define	GetMaxY() 			(DISP_HOR_RESOLUTION-1)
#define ORIENTATION_REGISTER	0x0060  // Vertical rotation	 - A[5]=1; A[6]=0; A[7]=1;

#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)

#define	GetMaxY() 			(DISP_VER_RESOLUTION-1)
#define ORIENTATION_REGISTER	0x0000  // Horizontal rotation   - A[5]=0; A[6]=0; A[7]=0;

#endif

// Definition for memory page size with virtual display taken into account
// The maximum memory space of SSD1928 is 262kbyte
#ifndef PAGE_MEM_SIZE
// Memory allocation for a single page
#define PAGE_MEM_SIZE 	(GetMaxX()+1)*(GetMaxY()+1)*COLOR_DEPTH/8

#if PAGE_MEM_SIZE > 1215000ul	//this is the memory boundary of ssd1963
#error MEMORY ALLOCATION FAILED. CHECK SSD1963.h
#endif

#endif

/*********************************************************************
* Macros:  SetActivePage(page)
*
* Overview: Sets active graphic page.
*
* PreCondition: none
*
* Input: page - Graphic page number.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define LCD_SetActivePage(page)	_activePage = page

/*********************************************************************
* Function: void Clear(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: clears screen with current color
*
* Note: none
*
********************************************************************/
void LCD_Clear(uint16_t color);
void LCD_ClearArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
*
* Overview: Puts pixel with the given x,y coordinate position.
*
* PreCondition: none
*
* Input: x - x position of the pixel.
*		 y - y position of the pixel.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void LCD_PutPixel(uint16_t x, uint16_t y, uint16_t color);

/*********************************************************************
* Macros: SetClipRgn(left, top, right, bottom)
*
* Overview: Sets clipping region.
*
* PreCondition: none
*
* Input: left - Defines the left clipping region border.
*		 top - Defines the top clipping region border.
*		 right - Defines the right clipping region border.
*	     bottom - Defines the bottom clipping region border.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define LCD_SetClipRgn(left,top,right,bottom) _clipLeft=left; _clipTop=top; _clipRight=right; _clipBottom=bottom;

/*********************************************************************
* Macros: GetClipLeft()
*
* Overview: Returns left clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Left clipping border.
*
* Side Effects: none
*
********************************************************************/
#define LCD_GetClipLeft() _clipLeft

/*********************************************************************
* Macros: GetClipRight()
*
* Overview: Returns right clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Right clipping border.
*
* Side Effects: none
*
********************************************************************/
#define LCD_GetClipRight() _clipRight

/*********************************************************************
* Macros: GetClipTop()
*
* Overview: Returns top clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Top clipping border.
*
* Side Effects: none
*
********************************************************************/
#define LCD_GetClipTop() _clipTop

/*********************************************************************
* Macros: GetClipBottom()
*
* Overview: Returns bottom clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Bottom clipping border.
*
* Side Effects: none
*
********************************************************************/
#define LCD_GetClipBottom() _clipBottom

/*********************************************************************
* Macros: SetClip(control)
*
* Overview: Enables/disables clipping.
*
* PreCondition: none
*
* Input: control - Enables or disables the clipping.
*			- 0: Disable clipping
*			- 1: Enable clipping
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define LCD_SetClip(control) _clipRgn=control;

/*********************************************************************
* Macros: IsDeviceBusy()
*
* Overview: Returns non-zero if LCD controller is busy
*           (previous drawing operation is not completed).
*
* PreCondition: none
*
* Input: none
*
* Output: Busy status.
*
* Side Effects: none
*
********************************************************************/
#define LCD_IsDeviceBusy()  0

/*********************************************************************
* Macros: SetPalette(colorNum, color)
*
* Overview:  Sets palette register.
*
* PreCondition: none
*
* Input: colorNum - Register number.
*        color - Color.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define LCD_SetPalette(colorNum, color)

/*********************************************************************
* Function:  LCD_SetArea(start_x,start_y,end_x,end_y)
*
* PreCondition: SetActivePage(page)
*
* Input: start_x, end_x	- start column and end column
*		 start_y,end_y 	- start row and end row position (i.e. page address)
*
* Output: none
*
* Side Effects: none
*
* Overview: defines start/end columns and start/end rows for memory access
*			from host to SSD1963
* Note: none
********************************************************************/
void LCD_SetArea(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

/*********************************************************************
* Function:  SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* PreCondition: none
*
* Input: top - Top Fixed Area in number of lines from the top
*				of the frame buffer
*		 scroll - Vertical scrolling area in number of lines
*		 bottom - Bottom Fixed Area in number of lines
*
* Output: none
*
* Side Effects: none
*
* Overview:
*
* Note: Reference: section 9.22 Set Scroll Area, SSD1963 datasheet Rev0.20
*
********************************************************************/
void LCD_SetScrollArea(uint16_t top, uint16_t scroll, uint16_t bottom);

/*********************************************************************
* Function:  void  SetScrollStart(SHORT line)
*
* Overview: First, we need to define the scrolling area by SetScrollArea()
*			before using this function.
*
* PreCondition: SetScrollArea(SHORT top, SHORT scroll, SHORT bottom)
*
* Input: line - Vertical scrolling pointer (in number of lines) as
*		 the first display line from the Top Fixed Area defined in SetScrollArea()
*
* Output: none
*
* Note: Example -
*
*		SHORT line=0;
*		SetScrollArea(0,272,272);
*		for(line=0;line<272;line++) {SetScrollStart(line);DelayMs(100);}
*
*		Code above scrolls the whole page upwards in 100ms interval
*		with page 2 replacing the first page in scrolling
********************************************************************/
void LCD_SetScrollStart(uint16_t line);

/*********************************************************************
* Function:  void EnterSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 enters sleep mode
* Note: Host must wait 5mS after sending before sending next command
********************************************************************/
void LCD_EnterSleepMode (void);

/*********************************************************************
* Function:  void ExitSleepMode (void)
* PreCondition: none
* Input:  none
* Output: none
* Side Effects: none
* Overview: SSD1963 exits sleep mode
* Note:   cannot be called sooner than 15
********************************************************************/
void LCD_ExitSleepMode (void);


/*********************************************************************
* Function:  void  SetBacklight(BYTE intensity)
*
* Overview: This function makes use of PWM feature of ssd1963 to adjust
*			the backlight intensity.
*
* PreCondition: Backlight circuit with shutdown pin connected to PWM output of ssd1963.
*
* Input: 	(BYTE) intensity from
*			0x00 (total backlight shutdown, PWM pin pull-down to VSS)
*			0xff (99% pull-up, 255/256 pull-up to VDD)
*
* Output: none
*
* Note: The base frequency of PWM set to around 300Hz with PLL set to 120MHz.
*		This parameter is hardware dependent
********************************************************************/
uint8_t BacklightIntensity;
void LCD_SetBacklight(uint8_t intensity);


#define FADE_DOWN 0
#define FADE_UP 1
#define FADE_TO_NORMAL 2
void LCD_FadeBacklight(uint8_t fade);

/*********************************************************************
* Function:  void  SetTearingCfg(BOOL state, BOOL mode)
*
* Overview: This function enable/disable tearing effect
*
* PreCondition: none
*
* Input: 	BOOL state -	1 to enable
*							0 to disable
*			BOOL mode -		0:  the tearing effect output line consists
*								of V-blanking information only
*							1:	the tearing effect output line consists
*								of both V-blanking and H-blanking info.
* Output: none
*
* Note:
********************************************************************/
void LCD_SetTearingCfg(bool state, bool mode);



/*********************************************************************
* Function:  void  SetTearingCfg(BOOL state, BOOL mode)
*
* Overview: This function
*
* PreCondition: none
*
* Input:
*
*
* Output: none
*
* Note:
********************************************************************/
void LCD_Convert_Color565(uint16_t Color565);

#define DIR_TOP_TO_BOTTOM 0
#define DIR_BOTTOM_TO_TOP 1
void LCD_SetAddressOrder(bool direction);


void LCD_Delay(uint32_t nCount);


/************************************************************************
* Macro: Lo                                                             *
* Preconditions: None                                                   *
* Overview: This macro extracts a low byte from a 2 byte word.          *
* Input: None.                                                          *
* Output: None.                                                         *
************************************************************************/
#define Lo(X)   (uint8_t)(X&0x00ff)

/************************************************************************
* Macro: Hi                                                             *
* Preconditions: None                                                   *
* Overview: This macro extracts a high byte from a 2 byte word.         *
* Input: None.                                                          *
* Output: None.                                                         *
************************************************************************/
#define Hi(X)   (uint8_t)((X>>8)&0x00ff)





#endif /* INC_SSD1963_H_ */
