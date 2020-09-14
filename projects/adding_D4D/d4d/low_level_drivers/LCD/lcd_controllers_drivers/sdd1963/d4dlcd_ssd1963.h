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
* @file      d4dlcd_ssd1963.h
*
* @author     Petr Gargulak
*
* @version   0.0.2.0
*
* @date      Jun-4-2010
*
* @brief     D4D driver - ssd1963 lcd driver function header file
*
*******************************************************************************/

#ifndef __D4DLCD_SSD1963_H
#define __D4DLCD_SSD1963_H

  #if (D4D_MK_STR(D4D_LLD_LCD) == d4dlcd_ssd1963_ID)

    /******************************************************************************
    * Includes
    ******************************************************************************/
    #include "../../../../d4dlcd_ssd1963_cfg.h"

    /******************************************************************************
    * Constants
    ******************************************************************************/

// SSD1963 command table
#define CMD_NOP					0x00	//No operation
#define CMD_SOFT_RESET			0x01	//Software reset
#define CMD_GET_PWR_MODE		0x0A	//Get the current power mode
#define CMD_GET_ADDR_MODE		0x0B	//Get the frame memory to the display panel read order
#define CMD_GET_PIXEL_FORMAT	0x0C	//Get the current pixel format
#define CMD_GET_DISPLAY_MODE	0x0D	//Returns the display mode
#define CMD_GET_SIGNAL_MODE		0x0E	//
#define CMD_GET_DIAGNOSTIC		0x0F
#define CMD_ENT_SLEEP			0x10
#define CMD_EXIT_SLEEP			0x11
#define CMD_ENT_PARTIAL_MODE	0x12
#define CMD_ENT_NORMAL_MODE		0x13
#define CMD_EXIT_INVERT_MODE	0x20
#define CMD_ENT_INVERT_MODE		0x21
#define CMD_SET_GAMMA			0x26
#define CMD_BLANK_DISPLAY		0x28
#define CMD_ON_DISPLAY			0x29
#define CMD_SET_COLUMN			0x2A
#define CMD_SET_PAGE			0x2B
#define CMD_WR_MEMSTART			0x2C
#define CMD_RD_MEMSTART			0x2E
#define CMD_SET_PARTIAL_AREA	0x30
#define CMD_SET_SCROLL_AREA		0x33
#define CMD_SET_TEAR_OFF		0x34	//synchronization information is not sent from the display
#define CMD_SET_TEAR_ON			0x35	//sync. information is sent from the display
#define CMD_SET_ADDR_MODE		0x36	//set fram buffer read order to the display panel
#define CMD_SET_SCROLL_START	0x37
#define CMD_EXIT_IDLE_MODE		0x38
#define CMD_ENT_IDLE_MODE		0x39
#define CMD_SET_PIXEL_FORMAT	0x3A	//defines how many bits per pixel is used
#define CMD_WR_MEM_AUTO			0x3C
#define CMD_RD_MEM_AUTO			0x3E
#define CMD_SET_TEAR_SCANLINE	0x44
#define CMD_GET_SCANLINE		0x45
#define CMD_RD_DDB_START		0xA1
#define CMD_RD_DDB_AUTO			0xA8
#define CMD_SET_PANEL_MODE		0xB0
#define CMD_GET_PANEL_MODE		0xB1
#define CMD_SET_HOR_PERIOD		0xB4
#define CMD_GET_HOR_PERIOD		0xB5
#define CMD_SET_VER_PERIOD		0xB6
#define CMD_GET_VER_PERIOD		0xB7
#define CMD_SET_GPIO_CONF		0xB8
#define CMD_GET_GPIO_CONF		0xB9
#define CMD_SET_GPIO_VAL		0xBA
#define CMD_GET_GPIO_STATUS		0xBB
#define CMD_SET_POST_PROC		0xBC
#define CMD_GET_POST_PROC		0xBD
#define CMD_SET_PWM_CONF		0xBE
#define CMD_GET_PWM_CONF		0xBF
#define CMD_SET_LCD_GEN0		0xC0
#define CMD_GET_LCD_GEN0		0xC1
#define CMD_SET_LCD_GEN1		0xC2
#define CMD_GET_LCD_GEN1		0xC3
#define CMD_SET_LCD_GEN2		0xC4
#define CMD_GET_LCD_GEN2		0xC5
#define CMD_SET_LCD_GEN3		0xC6
#define CMD_GET_LCD_GEN3		0xC7
#define CMD_SET_GPIO0_ROP		0xC8
#define CMD_GET_GPIO0_ROP		0xC9
#define CMD_SET_GPIO1_ROP		0xCA
#define CMD_GET_GPIO1_ROP		0xCB
#define CMD_SET_GPIO2_ROP		0xCC
#define CMD_GET_GPIO2_ROP		0xCD
#define CMD_SET_GPIO3_ROP		0xCE
#define CMD_GET_GPIO3_ROP		0xCF
#define CMD_SET_ABC_DBC_CONF	0xD0
#define CMD_GET_ABC_DBC_CONF	0xD1
#define CMD_SET_DBC_HISTO_PTR	0xD2
#define CMD_GET_DBC_HISTO_PTR	0xD3
#define CMD_SET_DBC_THRES		0xD4
#define CMD_GET_DBC_THRES		0xD5
#define CMD_SET_ABM_TMR			0xD6
#define CMD_GET_ABM_TMR			0xD7
#define CMD_SET_AMB_LVL0		0xD8
#define CMD_GET_AMB_LVL0		0xD9
#define CMD_SET_AMB_LVL1		0xDA
#define CMD_GET_AMB_LVL1		0xDB
#define CMD_SET_AMB_LVL2		0xDC
#define CMD_GET_AMB_LVL2		0xDD
#define CMD_SET_AMB_LVL3		0xDE
#define CMD_GET_AMB_LVL3		0xDF
#define CMD_PLL_START			0xE0	//start the PLL
#define CMD_PLL_STOP			0xE1	//disable the PLL
#define CMD_SET_PLL_MN			0xE2
#define CMD_GET_PLL_MN			0xE3
#define CMD_GET_PLL_STATUS		0xE4	//get the current PLL status
#define CMD_ENT_DEEP_SLEEP		0xE5
#define CMD_SET_PCLK			0xE6	//set pixel clock (LSHIFT signal) frequency
#define CMD_GET_PCLK			0xE7	//get pixel clock (LSHIFT signal) freq. settings
#define CMD_SET_DATA_INTERFACE	0xF0
#define CMD_GET_DATA_INTERFACE	0xF1

/* LCD Panel settings */


#define DISP_HOR_RESOLUTION 800
#define DISP_VER_RESOLUTION 480

//#define DISP_ORIENTATION 90
#define DISP_ORIENTATION 0


#define DISPLAY_MODE_8 1
//#define DISPLAY_MODE_16 1
//#define DISPLAY_MODE_16_565

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




    /******************************************************************************
    * Types
    ******************************************************************************/

    /******************************************************************************
    * Macros
    ******************************************************************************/

    /******************************************************************************
    * Global variables
    ******************************************************************************/

		#ifdef D4D_LLD_LCD_HW
		  extern const D4DLCDHW_FUNCTIONS D4D_LLD_LCD_HW;
		#endif

    /******************************************************************************
    * Global functions
    ******************************************************************************/


  #endif
#endif /* __D4DLCD_SSD1963_H */










