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
* @file      d4dtch_ft5x06.c
*
* @author     Petr Gargulak
*
* @version   0.0.7.0
*
* @date      Jan-14-2014
*
* @brief     D4D driver - ft5x06 touch screen driver source c file
*
******************************************************************************/

#include "../../../../d4d.h"            // include of all public items (types, function etc) of D4D driver
#include "../../../../common_files/d4d_lldapi.h"     // include non public low level driver interface header file (types, function prototypes, enums etc. )
#include "../../../../common_files/d4d_private.h"    // include the private header file that contains perprocessor macros as D4D_MK_STR
#include "chip.h"


// identification string of driver - must be same as name D4DTCH_FUNCTIONS structure + "_ID"
// it is used for enable the code for compilation
#define d4dtch_ft5x06_ID 1


// copilation enable preprocessor condition
// the string d4dtch_ft5x06_ID must be replaced by define created one line up
#if (D4D_MK_STR(D4D_LLD_TCH) == d4dtch_ft5x06_ID)

  // include of low level driver heaser file
  // it will be included into wole project only in case that this driver is selected in main D4D configuration file
  #include "d4dtch_ft5x06.h"
  /******************************************************************************
  * Macros
  ******************************************************************************/

  /******************************************************************************
  * Internal function prototypes
  ******************************************************************************/

  static unsigned char D4DTCH_Init_Ft5x06(void);
  static unsigned char D4DTCH_DeInit_Ft5x06(void);
  static D4D_TOUCHSCREEN_LIMITS* D4DTCH_GetRawLimits_Ft5x06(void);
  static unsigned char D4DTCH_GetPositionRaw_Ft5x06(unsigned short *TouchPositionX,
                                         unsigned short *TouchPositionY);

  /**************************************************************//*!
  *
  * Global variables
  *
  ******************************************************************/

  // the main structure that contains low level driver api functions
  // the name of this structure is used for recognizing of configured low level driver of whole D4D
  // so this name has to be used in main configuration header file of D4D driver to enable this driver
  const D4DTCH_FUNCTIONS d4dtch_ft5x06 ={
     D4DTCH_Init_Ft5x06,
     D4DTCH_GetPositionRaw_Ft5x06,
     D4DTCH_GetRawLimits_Ft5x06,
     D4DTCH_DeInit_Ft5x06
  };

  const D4D_TOUCHSCREEN_LIMITS d4dtchhw_ft5x06_limits ={
        D4DTCH_FULL_SCALE,
        D4DTCH_X_TOUCH_MIN,
        D4DTCH_Y_TOUCH_MIN,
        D4DTCH_X_TOUCH_OFFMAX,
        D4DTCH_Y_TOUCH_OFFMAX
  };


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
  * Begin of D4D_TCH public functions
  *//*! @addtogroup doxd4d_tch_func
  * @{
  *******************************************************************************/

  /**************************************************************************/ /*!
  * @brief   The function is used for initialization of this low level driver
  * @return  result: 1 - Success; 0 - Failed
  * @note    This should initilize all neccessary things to run ft5x06 touch screen driver.
  *******************************************************************************/
  static unsigned char D4DTCH_Init_Ft5x06(void)
  {
	  /* Configure GPIO interrupt pin as input */
	  	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIO_INTERRUPT_PORT, GPIO_INTERRUPT_PIN);
	  	/* Configure the GPIO interrupt */
	  	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);

	  	/* Enable interrupt in the NVIC */
	  	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
	  	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);


	  	Chip_I2C_Init(FT5x06_I2C_BUS); // Initialize I2C
	  	Chip_I2C_SetClockRate(FT5x06_I2C_BUS, SPEED_400KHZ);

	  	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 0, IOCON_FUNC3);
	  	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 1, IOCON_FUNC3);

	  	NVIC_DisableIRQ(I2C1_IRQn);

	  	Chip_I2C_SetMasterEventHandler(FT5x06_I2C_BUS, Chip_I2C_EventHandlerPolling);
    return 1;
  }

  /**************************************************************************/ /*!
  * @brief   The function is used for deinitialization of this low level driver
  * @return  result: 1 - Success; 0 - Failed
  * @note    This should deinitilize all neccessary things to run ft5x06 touch screen driver.
  *******************************************************************************/
  static unsigned char D4DTCH_DeInit_Ft5x06(void)
  {
    return 0;
  }

  /**************************************************************************/ /*!
  * @brief   The function returns pointer on touch screen raw limits structure.
  * @return  pointer on touch screen raw limit structure
  * @note    This structure is used to calibrate the touch screen algorithm
  *******************************************************************************/
  static D4D_TOUCHSCREEN_LIMITS* D4DTCH_GetRawLimits_Ft5x06(void)
  {
    return (D4D_TOUCHSCREEN_LIMITS*)&d4dtchhw_ft5x06_limits;
  }

  /**************************************************************************/ /*!
  * @brief   Reads  touch screen and returns raw uncompensated X, Y coordinates if screen touched
  * @param   TouchPositionX - Pointer to X coordinate
  * @param   TouchPositionY - Pointer to Y coordinate
  * @return  0 - no screen touch;  1 - screen touch,
  * @note    This functon is used to get the touch screen events
  *******************************************************************************/
  static unsigned char D4DTCH_GetPositionRaw_Ft5x06 (unsigned short *TouchPositionX,
                                         unsigned short *TouchPositionY)
  {
	uint8_t reg = prvBaseRegisterForPoint[0];
	//I2C2_Transmit(FT5206_ADDRESS, &reg, 1);
	uint8_t storage[4] = {0x00};
	//I2C2_Receive(FT5206_ADDRESS, storage, 4);
	//pide cuatro bytes y se almacenan por referencia en storage
	Chip_I2C_MasterCmdRead(FT5x06_I2C_BUS, FT5206_ADDRESS, reg, storage, 4);


	uint8_t event = (storage[0] & 0xC0) >> 6; // en bit 7 y 8 del primer byte se almacenan put down/put up/contact
	*TouchPositionX = ((storage[0] & 0x0F) << 8) | storage[1]; //primeros 4 bit del byte alto y 8 bit del bajo
	*TouchPositionY = ((storage[2] & 0x0F) << 8) | storage[3]; //primeros 4 bit del byte alto y 8 bit del bajo
	if(event==2) // contacto
	{
		return 1;
	}
	else
	{
		return 0;
	}

  }

  /*! @} End of doxd4d_tch_func                                         */

#endif //(D4D_MK_STR(D4D_LLD_TCH) == d4dtch_ft5x06_ID)
