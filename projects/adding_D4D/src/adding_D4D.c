/*
===============================================================================
 Name        : adding_D4D.c
 Author      : Julian Botello, Gonzalo Aranguiz
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
/**
 * @file adding_D4D.c
 * @brief Programa principal, con inicialización y bucle infinito.
 *
 * Se inicializan las variables necesarias y se configuran los puertos mediante drivers,
 * para luego llamar continuamente a la función handler de la librería gráfica que
 * refresca la pantalla.
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
#include "actuador_festo.h"
#include "load_cell_30.h"
#include "uart.h"


uint32_t tiempo_ms = 0; /**< Contador en ms para marcar el tiempo en los datos de presión.*/
bool pulsado = FALSE; /**< Bandera para accionamiento del pulsador participante. */
D4D_EXTERN_SCREEN(screen_main) //JB: declaracion del nombre de la pantalla principal

/**
 * @brief Incrementa el contador cada 1 ms.
 */
void SysTick_Handler(void){
	tiempo_ms++;
}

/**
 * @brief Código ejecutado en la interrupción de la tecla 1.
 *
 * Introduce en la cola de eventos de la librería gráfica la pulsación
 * de la tecla, y luego un retardo de 80 ms para evitar rebote.
 */
void FuncionTecla_1 (){
	//Código de la tecla 1 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_UP);
	DelayMs(80);
}

/**
 * @brief Código ejecutado en la interrupción de la tecla 2.
 *
 * Introduce en la cola de eventos de la librería gráfica la pulsación
 * de la tecla, y luego un retardo de 80 ms para evitar rebote.
 */
void FuncionTecla_2 (){
	//Código de la tecla 2 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_DOWN);
	DelayMs(80);
}

/**
 * @brief Código ejecutado en la interrupción de la tecla 3.
 *
 * Introduce en la cola de eventos de la librería gráfica la pulsación
 * de la tecla, y luego un retardo de 80 ms para evitar rebote.
 */
void FuncionTecla_3 (){
	//Código de la tecla 3 en la interrupción
	D4D_NewKeyEvent(D4D_KEY_SCANCODE_ENTER);
	DelayMs(80);
}

/**
 * @brief Código ejecutado en la interrupción de la tecla 4.
 *
 * Introduce en la cola de eventos de la librería gráfica la pulsación
 * de la tecla, y luego un retardo de 80 ms para evitar rebote.
 */
void FuncionTecla_4 (){
	//Código de la tecla 4 en la interrupción
	if(D4D_GetActiveScreen()!=&screen_main){
		D4D_NewKeyEvent(D4D_KEY_SCANCODE_ESC);
	}
}

/**
 * @brief Código ejecutado en la interrupción del pulsador participante.
 *
 * Envía la instrucción de retroceso al actuador, cambia de estado la salida
 * de trigger y levanta la bandera de pulsado.
 */
void FuncionPulsPart(){
	MoverActuador(RETRO);
	GPIOToggle(GPIO_SPI_MOSI_TRIG);
	pulsado = TRUE;
}

/**
 * @brief Inicialización de los drivers del sistema.
 */
void SysInit(void)
{
	// Inicialización de puertos GPIO para actuador, clock, leds, teclas
	SystemClockInit();
	InitActuador();
	Ready4read(); //Celda de carga
	SwitchesInit();
	SwitchActivInt(SWITCH_1,FuncionTecla_1);
	SwitchActivInt(SWITCH_2,FuncionTecla_2);
	SwitchActivInt(SWITCH_3,FuncionTecla_3);
	SwitchActivInt(SWITCH_4,FuncionTecla_4);
	LedsInit();

	//Inicialización de gpio para pulsador participante y su interrupción
	GPIOInit(GPIO_RXD0_PP, GPIO_INPUT);
	GPIOActivInt(GPIOGP4, GPIO_RXD0_PP, FuncionPulsPart, 0);//Por flanco descendente

	//Inicialización de Trigger para BioAmp
	GPIOInit(GPIO_SPI_MOSI_TRIG, GPIO_OUTPUT);

	// Inicialización del puerto UART
	serial_config UART_USB;
	UART_USB.baud_rate = 115200;
	UART_USB.port = SERIAL_PORT_PC;
	UART_USB.pSerial = NULL;

	UartInit(&UART_USB);
}

/**
 * @brief Función principal
 *
 * Ejecuta inicialización, configura el temporizador SysTick cada 1 ms, inicializa la pantalla principal,
 * define orientación horizontal y llama periodicamente al handler de la librería gráfica que refresca la pantalla.
 * @return
 */
int main(void) {

	SysInit();

    /* Enable and setup SysTick Timer at a periodic rate */
    SysTick_Config(SystemCoreClock/1000); // cada 1 ms

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

    return 0 ;
}
