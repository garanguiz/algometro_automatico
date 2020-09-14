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
 * @file      d4dlcdhw_lpc1769.c
 *
 * @author     Petr Gargulak
 *
 * @version   0.0.9.0
 *
 * @date      Jan-14-2014
 *
 * @brief     D4D driver - lpc1769 hardware lcd driver source c file
 *
 ******************************************************************************/

#include "d4d.h"            // include of all public items (types, function etc) of D4D driver
#include "common_files/d4d_lldapi.h"     // include non public low level driver interface header file (types, function prototypes, enums etc. )
#include "common_files/d4d_private.h"    // include the private header file that contains perprocessor macros as D4D_MK_STR
#include "SSD1963.h"   // LUEGO DE TERMINAR ESTA FUENTE, SE DEBE QUITAR --> XQ SE PASARON LAS DECLARACIONES EN _cfg.h
#include "stdbool.h"
#include "lpc_types.h"
#include "chip.h"
/******************************************************************************
 * D4D LCD HW Driver setting  constants
 *
 *//*! @addtogroup doxd4d_lcdhw_const
 * @{
 *******************************************************************************/

/*! @brief  Identification string of driver - must be same as name D4DLCDHW_FUNCTIONS structure + "_ID"
 it is used for enable the code for compilation   */
#define d4dlcdhw_lpc1769_ID 1// aca va 1


/*! @} End of doxd4d_lcdhw_const                                             */

// Compilation enable preprocessor condition
// the string d4dtch_lpc1769_ID must be replaced by define created one line up

#if (D4D_MK_STR(D4D_LLD_LCD_HW) == d4dlcdhw_lpc1769_ID)

// include of low level driver header file
// it will be included into whole project only in case that this driver is selected in main D4D configuration file
#include "low_level_drivers/LCD/lcd_hw_interface/lpc_1769/d4dlcdhw_lpc1769.h"
/******************************************************************************
 * Macros
 ******************************************************************************/

/******************************************************************************
 * Internal function prototypes
 ******************************************************************************/

static unsigned char D4DLCDHW_Init_Lpc1769(void);
static unsigned char D4DLCDHW_DeInit_Lpc1769(void);
static void D4DLCDHW_SendDataWord_Lpc1769(unsigned short value);
static void D4DLCDHW_SendCmdWord_Lpc1769(unsigned short cmd);
static unsigned short D4DLCDHW_ReadDataWord_Lpc1769(void);
static unsigned short D4DLCDHW_ReadCmdWord_Lpc1769(void);
static unsigned char D4DLCDHW_PinCtl_Lpc1769(D4DLCDHW_PINS pinId, D4DHW_PIN_STATE setState);
static void D4DLCD_FlushBuffer_Lpc1769(D4DLCD_FLUSH_MODE mode);

/******************************************************************************
 * D4D LCD HW Driver setting  variables
 *
 *//*! @addtogroup doxd4d_lcdhw_variable
 * @{
 *******************************************************************************/
/*! @brief the main structure that contains low level driver API functions
 the name fo this structure is used for recognizing of configured low level driver of whole D4D
 so this name has to be used in main configuration header file of D4D driver to enable this driver.
 */
const D4DLCDHW_FUNCTIONS d4dlcdhw_lpc1769 =
{
	D4DLCDHW_Init_Lpc1769, 			//LCD_Init(void);
	D4DLCDHW_SendDataWord_Lpc1769, 	//LCD_WriteData(uint16_t data);
	D4DLCDHW_SendCmdWord_Lpc1769,	//LCD_WriteCommand(uint16_t cmd);
	D4DLCDHW_ReadDataWord_Lpc1769,	//LCD_readData(void);
	D4DLCDHW_ReadCmdWord_Lpc1769,
	D4DLCDHW_PinCtl_Lpc1769,
	D4DLCD_FlushBuffer_Lpc1769,
	D4DLCDHW_DeInit_Lpc1769
};

/*! @} End of doxd4d_lcdhw_variable                                         */

/**************************************************************//*!
 *
 * Local variables
 *
 ******************************************************************/

/******************************************************************************
 * Begin of D4D_LCD HW public functions
 *//*! @addtogroup doxd4d_lcdhw_func
 * @{
 *******************************************************************************/

/**************************************************************************//*!
 * @brief   The function is used for initialization of this low level driver
 * @return  result: 1 - Success; 0 - Failed
 * @note    This should initilize all neccessary things to run lpc1769 lcd hardware interface driver.
 *******************************************************************************/
static unsigned char D4DLCDHW_Init_Lpc1769(void)
{
	//prende backlight
	Chip_GPIO_SetPinState(LPC_GPIO, D4DLCD_BACKLIGHT_PORT, D4DLCD_BACKLIGHT, true);
	/* Enable GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
    D4DLCD_INIT_CS;
    D4DLCD_INIT_DC;
    D4DLCD_INIT_RESET;
    D4DLCD_INIT_WR;
    D4DLCD_INIT_RD;
    D4DLCD_INIT_BACKLIGHT;
    D4DLCD_INIT_RL;
    D4DLCD_INIT_UD;

//  D4DLCD_INIT_DATA;
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT0,   IOCON_MODE_INACT , IOCON_FUNC0);\
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT1,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT2,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT3,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT4,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT5,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT6,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT7,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT8,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT9,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT10,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT11,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT12,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT13,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT14,   IOCON_MODE_INACT , IOCON_FUNC0);
    Chip_IOCON_PinMux(LPC_IOCON, DATA_PORT,  BIT15,   IOCON_MODE_INACT , IOCON_FUNC0);

    /*-- GPIO Configuration ------------------------------------------------------*/
    /* Control lines */
    // configura como salida a DC,RESET,WR,RD,UD,RL (true: salida | false:entrada)
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_CS_PORT    ,   D4DLCD_CS, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_DC_PORT ,      D4DLCD_DC, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_RESET_PORT ,   D4DLCD_RESET, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_WR_PORT ,      D4DLCD_WR, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_RD_PORT ,      D4DLCD_RD, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_UD_PORT ,      D4DLCD_UD, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_RL_PORT ,      D4DLCD_RL, true);
    // espeja la pantalla
    Chip_GPIO_SetPinState(LPC_GPIO, D4DLCD_RL_PORT, D4DLCD_RL, true);

    Chip_GPIO_SetPinDIR(LPC_GPIO, D4DLCD_BACKLIGHT_PORT, D4DLCD_BACKLIGHT, true);


    /* Data and command bus */
    // mapeo de puertos y config como salida
#ifdef DISPLAY_MODE_8
    uint32_t mask = (1<<BIT0)|(1<<BIT1)|(1<<BIT2)|(1<<BIT3)|(1<<BIT4)|(1<<BIT5)|(1<<BIT6)|(1<<BIT7);
    Chip_GPIO_SetPortDIR(LPC_GPIO, DATA_PORT, mask, true); // 0b1111111100
#endif
#ifdef DISPLAY_MODE_16_565
    uint32_t mask = (1<<BIT0)|(1<<BIT1)|(1<<BIT2)|(1<<BIT3)|(1<<BIT4)|(1<<BIT5)|(1<<BIT6)|(1<<BIT7)|(1<<BIT8)|
    (1<<BIT9)|(1<<BIT10)|(1<<BIT11)|(1<<BIT12)|(1<<BIT13)|(1<<BIT14)|(1<<BIT15);

    Chip_GPIO_SetPortDIR(LPC_GPIO, DATA_PORT, mask, true); // 0b11001111000111111111100
#endif

    /* Initiate control lines */
    D4DLCD_ASSERT_RD;
    D4DLCD_ASSERT_WR;
    D4DLCD_ASSERT_DC;
    D4DLCD_ASSERT_CS;

    /* LCD Reset line */
    D4DLCD_ASSERT_RESET;
    return 1;


}

/**************************************************************************//*!
 * @brief   The function is used for deinitialization of this low level driver
 * @return  result: 1 - Success; 0 - Failed
 * @note    This should deinitilize all neccessary things to run lpc1769 lcd hardware interface driver.
 *******************************************************************************/
static unsigned char D4DLCDHW_DeInit_Lpc1769(void)
{

	return 0; // failed because there in lpc1769 is no code
}

/**************************************************************************//*!
 * @brief   The function send the one 16 bit variable into LCD
 * @return  none
 * @param   value - value to send to LCD
 * @note    This function sends 16 bit data word to LCD
 *******************************************************************************/
static void D4DLCDHW_SendDataWord_Lpc1769(unsigned short value)
{
	D4DLCD_DEASSERT_CS;
	D4DLCD_ASSERT_RD;
	D4DLCD_ASSERT_DC;
	Chip_GPIO_SetPortValue(LPC_GPIO, DATA_PORT, ((value & 0x03FF)<<2) | ((value & 0x3C00)<<5) | ((value & 0xC000)<<7) );
	D4DLCD_DEASSERT_WR;
	D4DLCD_ASSERT_WR;
	D4DLCD_ASSERT_CS;
}

/**************************************************************************//*!
 * @brief   The function send the one 16 bit command into LCD
 * @return  none
 * @param   cmd - command to send to LCD
 * @note    This function sends 16 bit command word to LCD
 *******************************************************************************/
static void D4DLCDHW_SendCmdWord_Lpc1769(unsigned short cmd)
{
	D4DLCD_DEASSERT_CS;
	D4DLCD_ASSERT_RD;
	D4DLCD_DEASSERT_DC;
	Chip_GPIO_SetPortValue(LPC_GPIO, DATA_PORT, ((cmd & 0xFF)<<2) );
	D4DLCD_DEASSERT_WR;
	D4DLCD_ASSERT_WR;
	D4DLCD_ASSERT_CS;
}

/**************************************************************************//*!
 * @brief   The function reads the one 16 bit variable from LCD (if this function is supported)
 * @return  the read value
 * @note    This function reads 16 bit data word from LCD
 *******************************************************************************/
static unsigned short D4DLCDHW_ReadDataWord_Lpc1769(void)
{
	uint16_t data = 0x0000;
	uint32_t mask = (1<<BIT0)|(1<<BIT1)|(1<<BIT2)|(1<<BIT3)|(1<<BIT4)|(1<<BIT5)|(1<<BIT6)|(1<<BIT7);
	Chip_GPIO_SetPortDIR(LPC_GPIO, DATA_PORT, mask, false); // 0b1111111100
	D4DLCD_DEASSERT_CS; D4DLCD_ASSERT_DC; D4DLCD_DEASSERT_RD; D4DLCD_ASSERT_WR;
	// wait_us(10);
	// data = (GPIOC->IDR&0xFFFF);
	data = Chip_GPIO_GetPortValue(LPC_GPIO, DATA_PORT);
	D4DLCD_ASSERT_RD;
	D4DLCD_ASSERT_CS;
	Chip_GPIO_SetPortDIR(LPC_GPIO, DATA_PORT, mask, true);// 0b1111111100
	return (data>>2) & 0xFF;
}

/**************************************************************************//*!
 * @brief   The function reads the one 16 bit command from LCD (if this function is supported)
 * @return  the read command
 * @note    This function reads 16 bit command word from LCD
 *******************************************************************************/
static unsigned short D4DLCDHW_ReadCmdWord_Lpc1769(void)
{
	return 0;
}

/**************************************************************************//*!
 * @brief   The function allows control GPIO pins for LCD conrol purposes
 * @param   pinId - the pin definition
 * @param   setState - the pin action/state definition
 * @return  for Get action retuns the pin value
 * @note    This function controls the additional control pins
 *******************************************************************************/
static unsigned char D4DLCDHW_PinCtl_Lpc1769(D4DLCDHW_PINS pinId, D4DHW_PIN_STATE setState)
{
	return 0; // es usada esta función o puedo realizarla con Chip_IOCON_PinMux?
}

/**************************************************************************//*!
 * @brief   For buffered low level interfaces is used to inform
 *            driver the complete object is drawed and pending pixels should be flushed
 * @param   mode - mode of Flush
 * @return  none
 * @note    This function just notify the driver that eGUI finish drawing element/object/screen to allow driver handle any kind of caching memmory.
 *******************************************************************************/
static void D4DLCD_FlushBuffer_Lpc1769(D4DLCD_FLUSH_MODE mode)
{

}

/*! @} End of doxd4d_lcdhw_func                                         */

#endif //(D4D_MK_STR(D4D_LLD_LCD_HW) == d4dlcdhw_lpc1769_ID)

