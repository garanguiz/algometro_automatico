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
* @file      d4dtch_ft5x06.h
*
* @author     Petr Gargulak
*
* @version   0.0.2.0
*
* @date      Apr-30-2010
*
* @brief     D4D driver - ft5x06 touch screen driver function header file
*
*******************************************************************************/

#ifndef __D4DTCH_FT5X06_H
#define __D4DTCH_FT5X06_H

  #if (D4D_MK_STR(D4D_LLD_TCH) == d4dtch_ft5x06_ID)

    /******************************************************************************
    * Includes
    ******************************************************************************/
    #include "../../../../d4dtch_ft5x06_cfg.h"

	/* FT5206 definitions */
	/* Private defines -----------------------------------------------------------*/
	#define FT5206_REGISTER_DEVICE_MODE 	(0x00)
	#define FT5206_REGISTER_GEST_ID 		(0x01)
	#define FT5206_REGISTER_TD_STATUS 		(0x02)

	#define FT5206_REGISTER_TOUCH1_XH 		(0x03)
	#define FT5206_REGISTER_TOUCH1_XL 		(0x04)
	#define FT5206_REGISTER_TOUCH1_YH 		(0x05)
	#define FT5206_REGISTER_TOUCH1_YL 		(0x06)

	#define FT5206_REGISTER_TOUCH2_XH 		(0x09)
	#define FT5206_REGISTER_TOUCH2_XL 		(0x0A)
	#define FT5206_REGISTER_TOUCH2_YH 		(0x0B)
	#define FT5206_REGISTER_TOUCH2_YL 		(0x0C)

	#define FT5206_REGISTER_TOUCH3_XH 		(0x0F)
	#define FT5206_REGISTER_TOUCH3_XL 		(0x10)
	#define FT5206_REGISTER_TOUCH3_YH 		(0x11)
	#define FT5206_REGISTER_TOUCH3_YL 		(0x12)

	#define FT5206_REGISTER_TOUCH4_XH 		(0x15)
	#define FT5206_REGISTER_TOUCH5_XH 		(0x1B)

	#define FT5206_REGISTER_ID_G_PERIODACTIVE (0x88)	/* The period of active status, value 3 to 14 (defualt 12) */
	#define FT5206_REGISTER_ID_G_CIPHER		(0xA3)	/* Chip vendor ID */
	#define FT5206_REGISTER_ID_G_MODE		(0xA4)	/* Interrupt mode */
	#define FT5206_REGISTER_ID_G_FT5201ID	(0xA8)	/* CTPM vendor ID */

	#define FT5206_ADDRESS			(0x38)
	#define FT5206_CHIP_VENDOR_ID	(0x55)
	#define FT5206_CTPM_VENDOR_ID	(0x86)


	/* GPIO pin for interrupt */
	#define GPIO_INTERRUPT_PIN     4	/* GPIO pin number mapped to interrupt */
	#define GPIO_INTERRUPT_PORT    GPIOINT_PORT2	/* GPIO port number mapped to interrupt */

	/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
	#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
	#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */


	#define FT5x06_I2C_BUS 				I2C1
	#define FT5x06_I2C_SCL				0, 1
	#define FT5x06_I2C_SDA				0, 0

	#define SPEED_100KHZ         100000
	#define SPEED_400KHZ         400000


    /******************************************************************************
    * Constants
    ******************************************************************************/
static const uint8_t prvBaseRegisterForPoint[5] = {
		FT5206_REGISTER_TOUCH1_XH,
		FT5206_REGISTER_TOUCH2_XH,
		FT5206_REGISTER_TOUCH3_XH,
		FT5206_REGISTER_TOUCH4_XH,
		FT5206_REGISTER_TOUCH5_XH
};
    /******************************************************************************
    * Types
    ******************************************************************************/

    /******************************************************************************
    * Macros
    ******************************************************************************/
#ifndef D4DTCH_FULL_SCALE
#define D4DTCH_FULL_SCALE           4096
#endif

#ifndef D4DTCH_X_TOUCH_MIN
#define D4DTCH_X_TOUCH_MIN           0
#endif

#ifndef D4DTCH_Y_TOUCH_MIN
#define D4DTCH_Y_TOUCH_MIN           0
#endif


#ifndef D4DTCH_X_TOUCH_OFFMAX
#define D4DTCH_X_TOUCH_OFFMAX           (D4DTCH_FULL_SCALE * 7/16)
#endif

#ifndef D4DTCH_Y_TOUCH_OFFMAX
#define D4DTCH_Y_TOUCH_OFFMAX           (D4DTCH_FULL_SCALE / 4)
#endif


    /******************************************************************************
    * Global variables
    ******************************************************************************/

    /******************************************************************************
    * Global functions
    ******************************************************************************/
void GPIO_IRQ_HANDLER(void)
{
	uint8_t pin = Chip_GPIOINT_GetStatusFalling(LPC_GPIOINT,GPIO_INTERRUPT_PORT);
	if( pin == (1 << GPIO_INTERRUPT_PIN))
	{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);
#if defined(MULTIPLE_TOUCH_POINTS)
	uint8_t numOfPoints = 0;
	uint8_t data = FT5206_REGISTER_TD_STATUS;
	//I2C2_TransmitFromISR(FT5206_ADDRESS, &data, 1);
	//I2C2_ReceiveFromISR(FT5206_ADDRESS, &numOfPoints, 1);
	Chip_I2C_MasterCmdRead(FT5x06_I2C_BUS, FT5206_ADDRESS, data, numOfPoints, 1);


	uint32_t i;
	for (i = 0; i < numOfPoints; i++)
	{
		uint8_t reg = prvBaseRegisterForPoint[i];
		//I2C2_TransmitFromISR(FT5206_ADDRESS, &reg, 1);
		uint8_t storage[4] = {0x00};
		//I2C2_ReceiveFromISR(FT5206_ADDRESS, storage, 4);
		Chip_I2C_MasterCmdRead(FT5x06_I2C_BUS, FT5206_ADDRESS, reg, storage, 4);

		LCDEventMessage message;
		message.event = LCDEvent_TouchEvent;
		message.data[0] = ((storage[0] & 0x0F) << 8) | storage[1];
		message.data[1] = ((storage[2] & 0x0F) << 8) | storage[3];
		message.data[2] = (storage[0] & 0xC0) >> 6;
		message.data[3] = i+1;
		xQueueSendToBackFromISR(xLCDEventQueue, &message, NULL);
	}
#else
	uint8_t reg = prvBaseRegisterForPoint[0];
	//I2C2_TransmitFromISR(FT5206_ADDRESS, &reg, 1);
	uint8_t storage[4] = {0x00};
	//I2C2_ReceiveFromISR(FT5206_ADDRESS, storage, 4);
	//Chip_I2C_MasterCmdRead(FT5x06_I2C_BUS, FT5206_ADDRESS, reg, storage, 4);
	D4D_CheckTouchScreen();

#endif
	}
}

  #endif
#endif /* __D4DTCH_FT5X06_H */










