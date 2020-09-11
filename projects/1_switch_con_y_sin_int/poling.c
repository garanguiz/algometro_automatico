int main(void) {
	uint8_t Tecla;
	bool bandera=TRUE;
	bool hold=TRUE;
	
	//otras variables
	SystemClockInit();
	//otras inicializaciones
	
	while(1) {
		
		if (bandera){
			Medir();
			Mostrar();
				//Código si bandera es TRUE
		} else {
				//Código si bandera es FALSE
		}
		
		
		
		
		
		
		Tecla = SwitchesRead();
		switch (Tecla) {
			case SWITCH_1:
			  //Código de la tecla 1
			  bandera!=bandera;
			  retardorebote(80);
			break;
			case SWITCH_2:
			  //Código de la tecla 2
			  Conteo=0;			  
			break;
			case SWITCH_3:
			   hold!=hold;
			   retardorebote(80);
				//Código de la tecla 3
			break;
			case SWITCH_4:
				//Código de la tecla 4
				
			break;
			}// switch
		} // while
	return 0;
} //main


