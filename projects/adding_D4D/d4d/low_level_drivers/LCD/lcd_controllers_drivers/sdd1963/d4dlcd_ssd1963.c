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
* @file      d4dlcd_ssd1963.c
*
* @author     Petr Gargulak
*
* @version   0.0.10.0
*
* @date      Jan-14-2014
*
* @brief     D4D driver - ssd1963 lcd driver source c file
*
******************************************************************************/

#include "../../../../d4d.h"            // include of all public items (types, function etc) of D4D driver
#include "../../../../common_files/d4d_lldapi.h"     // include non public low level driver interface header file (types, function prototypes, enums etc. )
#include "../../../../common_files/d4d_private.h"    // include the private header file that contains perprocessor macros as D4D_MK_STR
#include "../../../../low_level_drivers/LCD/lcd_hw_interface/lpc_4337/d4dlcdhw_lpc4337.c"

/******************************************************************************
* D4D LCD Driver setting  constants
*
*//*! @addtogroup doxd4d_lcd_const
* @{
*******************************************************************************/

/*! @brief  Identification string of driver - must be same as name D4DLCD_FUNCTIONS structure + "_ID"
 it is used for enable the code for compilation   */
#define d4dlcd_ssd1963_ID 1

/*! @} End of doxd4d_lcd_const                                             */

// copilation enable preprocessor condition
// the string d4dlcd_ssd1963_ID must be replaced by define created one line up
#if (D4D_MK_STR(D4D_LLD_LCD) == d4dlcd_ssd1963_ID)
//  #if (D4D_LLD_LCD == d4dlcd_ssd1963_ID)
  // include of low level driver heaser file
  // it will be included into wole project only in case that this driver is selected in main D4D configuration file
  #include "d4dlcd_ssd1963.h"
//  #include "low_level_drivers/LCD/lcd_hw_interface/common_drivers/d4dlcdhw_common.h"

  /******************************************************************************
  * Macros
  ******************************************************************************/
/******************************************************************************
  * Types
  ******************************************************************************/

  typedef struct
  {
    unsigned short address;
    unsigned char data;
  }D4DLCD_REGISTER;

  /******************************************************************************
  * Internal function prototypes
  ******************************************************************************/

  static unsigned char D4DLCD_Init_Ssd1963(void);
  static unsigned char D4DLCD_SetWindow_Ssd1963(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
  static unsigned char D4DLCD_SetOrientation_Ssd1963(D4DLCD_ORIENTATION new_orientation);
  static void D4DLCD_Send_PixelColor_Ssd1963(D4D_COLOR color) ;
  static D4D_COLOR D4DLCD_Read_PixelColor_Ssd1963(void);
  static void D4DLCD_Flush_Ssd1963(D4DLCD_FLUSH_MODE mode);
  static void D4DLCD_Delay_ms_Ssd1963(unsigned short period);
  static unsigned char D4DLCD_DeInit_Ssd1963(void);


  /**************************************************************//*!
  *
  * Global variables
  *
  ******************************************************************/

  /******************************************************************************
  * D4D LCD Driver setting  variables
  *
  *//*! @addtogroup doxd4d_lcd_variable
  * @{
  *******************************************************************************/
  /*! @brief the main structure that contains low level driver api functions
   the name fo this structure is used for recognizing of configured low level driver of whole D4D
   so this name has to be used in main configuration header file of D4D driver to enable this driver
  */
  const D4DLCD_FUNCTIONS d4dlcd_ssd1963 =
  {
    D4DLCD_Init_Ssd1963,             ///< The pointer to driver initialization function
    D4DLCD_SetWindow_Ssd1963,        ///< The pointer to driver set drawing window function
    D4DLCD_SetOrientation_Ssd1963,   ///< The pointer to driver set screen orientation function
    D4DLCD_Send_PixelColor_Ssd1963,  ///< The pointer to driver send pixel to LCD function
    D4DLCD_Read_PixelColor_Ssd1963,  ///< The pointer to driver get pixel from LCD function
    D4DLCD_Flush_Ssd1963,            ///< The pointer to driver flush written pixels to LCD function
    D4DLCD_Delay_ms_Ssd1963,         ///< The pointer to driver delay function
    D4DLCD_DeInit_Ssd1963,           ///< The pointer to driver deinitialization function
  };
  /*! @} End of doxd4d_lcd_variable                                           */
  /**************************************************************//*!
  *
  * Local variables
  *
  ******************************************************************/

  /**************************************************************//*!
  *
  * Functions bodies
  *
  ******************************************************************/
  /******************************************************************************
  * Begin of D4D_LCD public functions
  *//*! @addtogroup doxd4d_lcd_func
  * @{
  *******************************************************************************/

  /**************************************************************************/ /*!
  * @brief   The function is used for initialization of this low level driver
  * @return  result: 1 - Success; 0 - Failed
  * @note    This should initilize all neccessary things to run ssd1963 lcd driver.
  *******************************************************************************/
  static unsigned char D4DLCD_Init_Ssd1963(void)
  {
	  /* Configure the LCD Control pins --------------------------------------------*/
	  (void)D4D_LLD_LCD_HW.D4DLCDHW_Init();//LCD_CtrlLinesConfig();


	  D4DLCD_DEASSERT_RS;	 			//RST_LOW; // LCD1_RESET LOW

	  D4D_LLD_LCD.D4DLCD_Delay_ms(20);	   	//LCD_Delay(20000);
	  D4DLCD_ASSERT_RS;			//RST_HIGH; // LCD1_RESET HIGH
	  D4D_LLD_LCD.D4DLCD_Delay_ms(50);      /* delay 50 ms */

	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0x01);// Software reset
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0x01);// Software reset
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0x01);// Software reset
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0x01);// Software reset

	  D4D_LLD_LCD.D4DLCD_Delay_ms(20);	   	//LCD_Delay(20000);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0xe0);//START PLL
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);
	  D4D_LLD_LCD.D4DLCD_Delay_ms(20);//	   LCD_Delay(20000);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0xe0);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(0xe0); //START PLL
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x03);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x03);
	  D4D_LLD_LCD.D4DLCD_Delay_ms(20);	//	   LCD_Delay(20000);

	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PANEL_MODE);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PANEL_MODE);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x20);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x20);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x80);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x80);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord((HDP>>8)&0X00FF);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord((HDP>>8)&0X00FF);  //Set HDP
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(HDP&0X00FF);//	   	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(HDP&0X00FF);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord((VDP>>8)&0X00FF);//	   	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord((VDP>>8)&0X00FF);  //Set VDP
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(VDP&0X00FF);//	   	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(VDP&0X00FF);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);

	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_DATA_INTERFACE);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_DATA_INTERFACE);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x03);//	   estaba en x01 D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00); //pixel data format, 0x03 is 16bit(565 format);0x00 is for 8-bit
	   //Set the MN of PLL
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PLL_MN);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PLL_MN);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1d);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1d);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x02);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x02);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x54);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x54);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PCLK);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PCLK);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x04);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x04);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x6f);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x6f);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x47);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x47);
	   //Set front porch and back porch
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_HOR_PERIOD);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_HOR_PERIOD);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x04);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x04);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x20);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x20);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x2e);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x2e);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0xd2);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0xd2);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_VER_PERIOD);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_VER_PERIOD);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x02);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x02);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x0d);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x0d);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x17);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x17);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x16);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x16);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);

	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_COLUMN);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_COLUMN);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x03);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x03);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1f);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1f);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PAGE);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PAGE);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x00);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1f);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x1f);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_GPIO_CONF);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_GPIO_CONF);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x0f);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x0f);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_GPIO_VAL);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_GPIO_VAL);
	  D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x01);

	  D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_ON_DISPLAY);//	   D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_ON_DISPLAY);				// Turn on display; show the image on display



	  D4D_LLD_LCD.D4DLCD_Delay_ms(50);//	 	LCD_Delay(50000);


	  return 1;

  }

  /**************************************************************************/ /*!
  * @brief   The function is used for deinitialization of this low level driver
  * @return  result: 1 - Success; 0 - Failed
  * @note    This should deinitilize all neccessary things to run ssd1963 lcd driver.
  *******************************************************************************/
  static unsigned char D4DLCD_DeInit_Ssd1963(void)
  {
	  return 0;
  }

  /**************************************************************************/ /*!
  * @brief   The function sets the logic drawing window in memory of LCD driver
  * @param   x1 - left cordination of logic window
  * @param   y1 - top cordination of logic window
  * @param   x2 - right cordination of logic window
  * @param   y2 - bottom cordination of logic window
  * @return  result: 1 - Success; 0 - Failed
  * @note    After this function could be write/read pixels to/from LCD panel
  *******************************************************************************/
  static unsigned char D4DLCD_SetWindow_Ssd1963(unsigned short start_x, unsigned short start_y, unsigned short end_x, unsigned short end_y)
  {
	  uint16_t temp;
	  	uint16_t start_x1, end_x1;
	  	uint16_t start_y1, end_y1;
	  	long offset;

	  	//offset = (uint16_t)_activePage*(GetMaxY()+1);
	  	offset=0;

	  #if (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)
	  	start_x1 = start_x;
	  	end_x1 = end_x;
	  	start_y1 = start_y;
	  	end_y1 = end_y;
	  #elif (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)
	  	start_x1 = GetMaxY() - start_y;
	  	end_x1 = GetMaxY() - end_y;
	  	start_y1 = start_x;
	  	end_y1 = end_x;
	  #endif

	  	if (start_x1 > end_x1) {
	  		temp = end_x1;
	  		end_x1 = start_x1;
	  		start_x1 = temp;
	  	}
	  	if (start_y1 > end_y1) {
	  		temp = end_y1;
	  		end_y1 = start_y1;
	  		start_y1 = temp;
	  	}

	  	start_y1 = offset + start_y1;
	  	end_y1   = offset + end_y1;

	  	D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_COLUMN);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(start_x1>>8);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(start_x1);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(end_x1>>8);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(end_x1);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_PAGE);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(start_y1>>8);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(start_y1);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(end_y1>>8);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(end_y1);
	  	//PUTPIXEL DE LA D4D NO TIENE LCD_WriteCommand(CMD_WR_MEMSTART);
	  	D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_WR_MEMSTART);
	  	return 1; //sucess
  }

  /**************************************************************************/ /*!
  * @brief   The function set the new orientation of LCD
  * @param   new_orientation - new orientation of the LCD
  * @return  result: 1 - Success; 0 - Failed
  * @note    This function changes the orientation of LCD
  *******************************************************************************/
  static unsigned char D4DLCD_SetOrientation_Ssd1963(D4DLCD_ORIENTATION new_orientation)
  {

//	    unsigned short width, height;
//	    D4D_LLD_LCD_HW.D4DLCDHW_SendCmdWord(CMD_SET_ADDR_MODE);
//
//	    switch (new_orientation) {
//	        default: // Invalid! Fall through to landscape mode
//	        case Landscape:
//	            D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0x80); //1000 0000
//	            width = D4D_SCREEN_SIZE_LONGER_SIDE;
//	            height = D4D_SCREEN_SIZE_SHORTER_SIDE;
//	            break;
//	        case Portrait:
//	            D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0xb0);//1011 0000
//	            width = D4D_SCREEN_SIZE_SHORTER_SIDE;
//	            height = D4D_SCREEN_SIZE_LONGER_SIDE;
//	            break;
//	        case Landscape180:
//	            D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0xe8); //1110 0000
//	            width = D4D_SCREEN_SIZE_LONGER_SIDE;
//	            height = D4D_SCREEN_SIZE_SHORTER_SIDE;
//	            break;
//	        case Portrait180:
//	            D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(0xd0); //1101 0000
//	            width = D4D_SCREEN_SIZE_SHORTER_SIDE;
//	            height = D4D_SCREEN_SIZE_LONGER_SIDE;
//	            break;
//	    }
//	        (void) D4D_LLD_LCD.D4DLCD_SetWindow(0, 0, height, width); // x is shorter side in display
	        return 1;
  }

  /**************************************************************************/ /*!
  * @brief   The function send the one pixel into LCD drawing window
  * @param   color - value of pixel color
  * @return  none
  * @note    This function writes the one pixel to the opened drawing window by \ref  D4DLCD_SetWindow_Ssd1963 function.
  *           If the window is lager then 1 pixel the driver MUST autmatically increment the next pixel address.
  *******************************************************************************/
  static void D4DLCD_Send_PixelColor_Ssd1963(D4D_COLOR value)
  {
#ifdef D4D_COLOR_TRANSPARENT
    if(value == D4D_COLOR_TRANSPARENT)
      D4D_LLD_LCD_HW.D4DLCDHW_ReadDataWord();
    else
#endif
    {
      #if D4D_COLOR_SYSTEM != D4D_COLOR_SYSTEM_RGB565
        Word color = D4D_COLOR_RGB565(D4D_COLOR_GET_R(value), D4D_COLOR_GET_G(value), D4D_COLOR_GET_B(value));
        D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord(color);
      #else
        D4D_LLD_LCD_HW.D4DLCDHW_SendDataWord((unsigned short)value);
      #endif
    }

  }

  /**************************************************************************/ /*!
  * @brief   The function reads the one Pixel from LCD (if this function is supported)
  * @return  color - value of pixel color
  * @note    This function reads the one pixel from the opened drawing window by \ref  D4DLCD_SetWindow_Ssd1963 function.
  *           If the window is lager then 1 pixel the driver MUST autmatically increment the next pixel address.
  *******************************************************************************/
  static D4D_COLOR D4DLCD_Read_PixelColor_Ssd1963(void)
  {
return 0;
  }

  /**************************************************************************/ /*!
  * @brief   For buffered low level interfaces is used to inform
  *            driver the complete object is drawed and pending pixels should be flushed
  * @param   mode - mode of Flush
  * @return  none
  * @note    This function just notify the driver that eGUI finish drawing element/object/screen to allow driver handle any kind of caching memmory.
  *******************************************************************************/
  static void D4DLCD_Flush_Ssd1963(D4DLCD_FLUSH_MODE mode)
  {

  }

  //-----------------------------------------------------------------------------
  // FUNCTION:    D4DLCD_Delay_ms_Ssd1963
  // SCOPE:       Low Level Driver API function
  // DESCRIPTION: For do some small delays in ms
  //
  // PARAMETERS:  period - count of ms
  //
  // RETURNS:     none
  //-----------------------------------------------------------------------------
  /**************************************************************************/ /*!
  * @brief   For do some small delays in ms
  * @param   period - 1ms periods time
  * @return  none
  * @note    This function is just used to do some delays of eGUI (just for initialization purposes, not for run)
  *******************************************************************************/
  static void D4DLCD_Delay_ms_Ssd1963(unsigned short period)
  {
	  uint32_t nCount=period*1000;
	  for(; nCount != 0; nCount--);
  }







  /*! @} End of doxd4d_lcd_func                                           */

#endif //(D4D_MK_STR(D4D_LLD_LCD) == d4dlcd_ssd1963_ID)
