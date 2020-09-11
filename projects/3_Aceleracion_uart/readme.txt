ESP8266

Basado en Ejemplo sAPI - Ing. Eric Pernia.

Manejo de dos UARTs, USART2 (FTDI) y USART3 (RS232). Uso de leds y teclas de la placa.
Módulo externo: ESP01 (ESP8266)

Ambas UART se configuran 8-N-1 a 115200.

Permite verificar el funcionamiento de l módulo enviando comandos AT mediante las teclas:

Al iniciar envia, por el FTDI un mensaje. Se debe configurar un cliente de puerto serie.
 
"Interfaz de configuracion del modulo ESP8266"
"Tecla 1: Verifica comunicación con el modulo"
"Tecla 2: Informa version de firmware del modulo"
"Tecla 3: Lista los Access Points"
"Tecla 4: IP Address" 

Los parametros infrmados por el ESP8266 se reciben por USART3 y se envían a USART2 (FTDI) para ser presentados en pantalla.
