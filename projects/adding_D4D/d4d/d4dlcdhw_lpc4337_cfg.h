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
* @file      d4dlcdhw_lpc1769.h.example
*
* @author     Petr Gargulak
*
* @version   0.0.1.0
*
* @date      Apr-26-2010
*
* @brief     D4D driver - lpc1769 hardware lcd driver configuration header file
*
*******************************************************************************/

#ifndef __D4DLCDHW_LPC4337_CFG_H
#define __D4DLCDHW_LPC4337_CFG_H


  /******************************************************************************
  * includes
  ******************************************************************************/
  // include here what the driver need for run for example "derivative.h"
  // #include "derivative.h"    /* include peripheral declarations and more for S08 and CV1 */

  /******************************************************************************
  * Constants
  ******************************************************************************/


/*******************************************
  * Signals definition
  *******************************************/
#define D4DLCD_BL_PORT		4				// Lcd_Light_PIN	0
#define D4DLCD_BL_PIN 		9		// Lcd_Light_PORT 	2
#define D4DLCD_BL_GPIO_PORT	5
#define D4DLCD_BL_GPIO_PIN	13

#define D4DLCD_CS_PORT   	4	        	// CS_PIN	5
#define D4DLCD_CS_PIN   	10	           // CS_PORT	2
#define D4DLCD_CS_GPIO_PORT	5
#define D4DLCD_CS_GPIO_PIN	14

#define D4DLCD_DC_PORT      4	           // RS_PIN   1 //REGISTER SELECT: RS = 1 —–> Data Register RS = 0 —–> Command Code Register | D/C -> 1/0
#define D4DLCD_DC_PIN   	8	           // RS_PORT	2
#define D4DLCD_DC_GPIO_PORT	5
#define D4DLCD_DC_GPIO_PIN	12


#define D4DLCD_WR_PORT		4 	           // WR_PIN	2
#define D4DLCD_WR_PIN   	6	           // WR_PORT	2
#define D4DLCD_WR_GPIO_PORT	2
#define D4DLCD_WR_GPIO_PIN	6

#define D4DLCD_RD_PORT      4  	        	// RD_PIN	3
#define D4DLCD_RD_PIN   	5	    	    // RD_PORT	2
#define D4DLCD_RD_GPIO_PORT	2
#define D4DLCD_RD_GPIO_PIN	5

#define D4DLCD_RS_PORT      4 		     		// RST_PIN  6
#define D4DLCD_RS_PIN   	4 		    // RST_PORT	2
#define D4DLCD_RS_GPIO_PORT	2
#define D4DLCD_RS_GPIO_PIN	4

#define D4DLCD_UD_PORT		2	 					// UD_PIN 	8
#define D4DLCD_UD_PIN 		3				// UD_PORT	2
#define D4DLCD_UD_GPIO_PORT	5
#define D4DLCD_UD_GPIO_PIN	3

#define D4DLCD_RL_PORT	 	2				//RL_PIN	7
#define D4DLCD_RL_PIN	 	4				//RL_PORT	2
#define D4DLCD_RL_GPIO_PORT	5
#define D4DLCD_RL_GPIO_PIN	4

#define BIT0_PORT			6
#define BIT0_PIN			1
#define BIT0_GPIO_PORT		3
#define BIT0_GPIO_PIN		0

#define BIT1_PORT			6
#define BIT1_PIN			4
#define BIT1_GPIO_PORT		3
#define BIT1_GPIO_PIN		3

#define BIT2_PORT			6
#define BIT2_PIN			5
#define BIT2_GPIO_PORT		3
#define BIT2_GPIO_PIN		4

#define BIT3_PORT			6
#define BIT3_PIN			7
#define BIT3_GPIO_PORT		5
#define BIT3_GPIO_PIN		15

#define BIT4_PORT			6
#define BIT4_PIN			8
#define BIT4_GPIO_PORT		5
#define BIT4_GPIO_PIN		16

#define BIT5_PORT			6
#define BIT5_PIN			9
#define BIT5_GPIO_PORT		3
#define BIT5_GPIO_PIN		5

#define BIT6_PORT			6
#define BIT6_PIN			10
#define BIT6_GPIO_PORT		3
#define BIT6_GPIO_PIN		6

#define BIT7_PORT			6
#define BIT7_PIN			11
#define BIT7_GPIO_PORT		3
#define BIT7_GPIO_PIN		7

#define BIT8_PORT			3
#define BIT8_PIN			2
#define BIT8_GPIO_PORT		5
#define BIT8_GPIO_PIN		9

#define BIT9_PORT			7
#define BIT9_PIN			4
#define BIT9_GPIO_PORT		3
#define BIT9_GPIO_PIN		12

#define BIT10_PORT			4
#define BIT10_PIN			0
#define BIT10_GPIO_PORT		2
#define BIT10_GPIO_PIN		0

#define BIT11_PORT			4
#define BIT11_PIN			3
#define BIT11_GPIO_PORT		2
#define BIT11_GPIO_PIN		3

#define BIT12_PORT			4
#define BIT12_PIN			2
#define BIT12_GPIO_PORT		2
#define BIT12_GPIO_PIN		2

#define BIT13_PORT			1
#define BIT13_PIN			5
#define BIT13_GPIO_PORT		1
#define BIT13_GPIO_PIN		8

#define BIT14_PORT			7
#define BIT14_PIN			5
#define BIT14_GPIO_PORT		3
#define BIT14_GPIO_PIN		13

#define BIT15_PORT			4
#define BIT15_PIN			1
#define BIT15_GPIO_PORT		2
#define BIT15_GPIO_PIN		1
/*******************************************
  * Display mode
  *******************************************/
//#define DISPLAY_MODE_8 1
#define DISPLAY_MODE_16_565 1


/*********** Power macros - for modification uncoment and modify ***********/




#define D4DLCD_INIT_CS				Chip_SCU_PinMuxSet(D4DLCD_CS_PORT, D4DLCD_CS_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);
#define D4DLCD_ASSERT_CS			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_CS_GPIO_PORT, D4DLCD_CS_GPIO_PIN, true);
#define D4DLCD_DEASSERT_CS 			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_CS_GPIO_PORT, D4DLCD_CS_GPIO_PIN, false);

#define D4DLCD_INIT_DC 				Chip_SCU_PinMuxSet(D4DLCD_DC_PORT, D4DLCD_DC_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);
#define D4DLCD_ASSERT_DC			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_DC_GPIO_PORT, D4DLCD_DC_GPIO_PIN, true);
#define D4DLCD_DEASSERT_DC			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_DC_GPIO_PORT, D4DLCD_DC_GPIO_PIN, false);

#define D4DLCD_INIT_WR				Chip_SCU_PinMuxSet(D4DLCD_WR_PORT, D4DLCD_WR_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);
#define D4DLCD_ASSERT_WR 			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_WR_GPIO_PORT, D4DLCD_WR_GPIO_PIN, true);
#define D4DLCD_DEASSERT_WR			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_WR_GPIO_PORT, D4DLCD_WR_GPIO_PIN, false);

#define D4DLCD_INIT_RD				Chip_SCU_PinMuxSet(D4DLCD_RD_PORT, D4DLCD_RD_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);
#define D4DLCD_ASSERT_RD 			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_RD_GPIO_PORT, D4DLCD_RD_GPIO_PIN, true);
#define D4DLCD_DEASSERT_RD 			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_RD_GPIO_PORT, D4DLCD_RD_GPIO_PIN, false);

#define D4DLCD_INIT_RS				Chip_SCU_PinMuxSet(D4DLCD_RS_PORT, D4DLCD_RS_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);
#define D4DLCD_ASSERT_RS			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_RS_GPIO_PORT, D4DLCD_RS_GPIO_PIN, true);
#define D4DLCD_DEASSERT_RS			Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_RS_GPIO_PORT, D4DLCD_RS_GPIO_PIN, false);

#define D4DLCD_INIT_BL		 		Chip_SCU_PinMuxSet(D4DLCD_BL_PORT, D4DLCD_BL_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);
#define D4DLCD_ASSERT_BL		 	Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_BL_GPIO_PORT, D4DLCD_BL_GPIO_PIN, true);
#define D4DLCD_DEASSERT_BL		 	Chip_GPIO_SetPinState(LPC_GPIO_PORT, D4DLCD_BL_GPIO_PORT, D4DLCD_BL_GPIO_PIN, false);

#define D4DLCD_INIT_UD				Chip_SCU_PinMuxSet(D4DLCD_UD_PORT, D4DLCD_UD_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);
#define D4DLCD_INIT_RL				Chip_SCU_PinMuxSet(D4DLCD_RL_PORT, D4DLCD_RL_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);


#define D4DLCD_INIT_DATA			do { \
									Chip_SCU_PinMuxSet(BIT0_PORT, BIT0_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT1_PORT, BIT1_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT2_PORT, BIT2_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT3_PORT, BIT3_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);\
									Chip_SCU_PinMuxSet(BIT4_PORT, BIT4_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);\
									Chip_SCU_PinMuxSet(BIT5_PORT, BIT5_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT6_PORT, BIT6_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT7_PORT, BIT7_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT8_PORT, BIT8_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC4);\
									Chip_SCU_PinMuxSet(BIT9_PORT, BIT9_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT10_PORT, BIT10_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT11_PORT, BIT11_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT12_PORT, BIT12_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT13_PORT, BIT13_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT14_PORT, BIT14_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									Chip_SCU_PinMuxSet(BIT15_PORT, BIT15_PIN, MD_PUP|MD_EZI|MD_ZI|FUNC0);\
									} while (0);







#endif /* __D4DLCDHW_LPC4337_CFG_H */
