bool bandera=TRUE;

void FuncionTecla_1 (){
	bandera=!bandera;
	//Código de la tecla 1 en la interrupción
	}
void FuncionTecla_2 (){
	//Código de la tecla 2 en la interrupción
	}
void FuncionTecla_3 (){
	//Código de la tecla 2 en la interrupción
	hold!=hold;
	}
void FuncionTecla_4 (){
	//Código de la tecla 2 en la interrupción
	Bandera=true;
	}

int main(void) {
	uint8_t Tecla;
	bool bandera=TRUE;
	//otras variables
	SystemClockInit();
	
	SwitchesInit();
	SwitchActivInt(SWITCH_1,FuncionTecla_1);
	SwitchActivInt(SWITCH_2,FuncionTecla_2);
	SwitchActivInt(SWITCH_3,FuncionTecla_3);
	SwitchActivInt(SWITCH_4,FuncionTecla_4);
	
	//otras inicializaciones
	while(1) {
		
		
		
		if (bandera){
			Medir();
			Mostrar();
				//Código si bandera es TRUE
		} else {
				//Código si bandera es FALSE
		}
		
		
	} // while
	return 0;
} //main



