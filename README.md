
![Logo FIUNER](logo_transparente.png)

-----------

Firmware del Proyecto Final de la carrera de Bioingeniería: "Prototipo para examen sensorial cuantitativo mecánico sincronizado con registros de electroencefalografía", basado en el firmware inicial para el desarrollo de drivers de aplicación y proyectos del cursado de la cátedra de Electrónica Programable con la plataforma [EDU-CIAA](www.proyecto-ciaa.com.ar/) basada en LPC4337JBD144. 

 *  [Campus Virtual de la Cátedra](http://campus.ingenieria.uner.edu.ar/course/view.php?id=190)
 *  [Repositorio oficial del proyecto CIAA.](https://github.com/ciaa)


**Autores:** 

 *  Aranguiz, Gonzalo (gonzalb9513@gmail.com)
 *  Mista, Christian(cmista@ingenieria.uner.edu.ar)
 *  Urteaga, Facundo (facundonahuelurteaga@ingenieria.uner.edu.ar)

Facultad de Ingeniería, Universidad Nacional de Entre Ríos, Argentina.

Se utiliza la librería gráfica [eGUI alias D4D](http://gargy007.github.io/egui_doc/) para generar una interfaz de usuario en una pantalla LCD. En la carpeta [projects/adding_D4D](projects/adding_D4D) se encuentra la aplicación principal [adding_D4D.c](projects/adding_D4D/src/adding_D4D.c), además de los archivos fuente que codifican cada ventana. En la carpeta [d4d](projects/adding_D4D/d4d) están los archivos de la librería gráfica. En [d4d_user_cfg.h](projects/adding_D4D/d4d/d4d_user_cfg.h) pueden configurarse las preferencias gráficas. Se encuentran implementados los drivers de bajo nivel necesarios para el funcionamiento con el microcontrolador de la EDU-CIAA y el controlador de la pantalla (ssd1963).
En la carpeta [drivers_devices](modules/lpc4337_m4/drivers_devices) se encuentran los drivers para el controlador Festo CMMO del actuador lineal EPCO y para el módulo HX711 que obtiene las lecturas de la celda de carga.




