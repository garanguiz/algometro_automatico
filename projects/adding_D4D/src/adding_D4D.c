/*
===============================================================================
 Name        : adding_D4D.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "../d4d/d4d.h" //JB
#include "../d4d/common_files/d4d_base.c"
#include "../d4d/common_files/d4d_imgdec_d4dint.c"
#include "chip.h"
#include "delay.h"
#include "variables_globales.h" // JB
#include "systemclock.h"
#include "led.h"
#include "switch.h"

D4D_EXTERN_SCREEN(screen_main) //JB: declaracion del nombre de la pantalla principal
//uint32_t cnt = 0;
void SysTick_Handler(void)
{	flag100ms=!flag100ms;
//	cnt ++;
//	cnt = cnt % 1000;
//	if (( cnt % 200) == 0)
//		D4D_CheckTouchScreen();
}
void FuncionTecla_1 (){
	//Código de la tecla 1 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_UP);
	DelayMs(80);
	}
void FuncionTecla_2 (){
	//Código de la tecla 2 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_DOWN);
	DelayMs(80);
	}
void FuncionTecla_3 (){
	//Código de la tecla 3 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_ENTER);
	DelayMs(80);
	}
void FuncionTecla_4 (){
	//Código de la tecla 4 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_ESC);
	DelayMs(80);
	}


// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {


    // Read clock settings and update SystemCoreClock variable
//    SystemCoreClockUpdate();
	SystemClockInit();
	SwitchesInit();
	SwitchActivInt(SWITCH_1,FuncionTecla_1);
	SwitchActivInt(SWITCH_2,FuncionTecla_2);
	SwitchActivInt(SWITCH_3,FuncionTecla_3);
	SwitchActivInt(SWITCH_4,FuncionTecla_4);
    // Set up and initialize all required blocks and
    // functions related to the board hardware
//    Board_Init();
	LedsInit();
    // Set the LED to the state of "On"
//    Board_LED_Set(0, true);
//	LedOn(LED_1);

    // TODO: insert code here
    //JB>

    /* Enable and setup SysTick Timer at a periodic rate */
    SysTick_Config(SystemCoreClock/100); // cada 10 ms?


    if(!D4D_Init(&screen_main))
      {
        // D4D initialization failed
//        printf("eGUI/D4D initialization failed\n\r");
      }

//     Setup right screen orientation
     D4D_SetOrientation(D4D_ORIENT_LANDSCAPE180);

    for(;;)
     {
       // Periodical call of the eGUI handler
       D4D_Poll();


     }


    //<JB

    return 0 ;
}
