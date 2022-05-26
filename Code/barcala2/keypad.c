#include "keypad.h"
#include "main.h"


void KEYPAD_init() {

	//Configuro el pull-up para las columnas (En 0)
	DDRD &=~(1<<PORTD2);
	DDRD &=~(1<<PORTD4);       //0bXX0000XX = DDRD (Entradas)
 	DDRD &=~(1<<PORTD5);
	DDRD &=~(1<<PORTD3);
	
	PORTD |= (1<<PORTD2);
	PORTD |= (1<<PORTD4);  //0bXX1111XX = PORTD Establece en 1 los bits de las columnas (Puerto D). Activo res de pull up (Entradas).
	PORTD |= (1<<PORTD5);
	PORTD |= (1<<PORTD3);
	
	PORTB  &=~ (1<<PORTB4);
	PORTB  &=~ (1<<PORTB3);      //0bXXX11XX1 = PORTB Establece en 0 los bits de las filas (Puerto B)(Salidas).
	PORTB  &=~ (1<<PORTB0);
	PORTD  &=~ (1<<PORTD7);     //0b1XXXXXXX = PORTD Establece 0 en el bit de fila (Puerto D)(Salida)
	
	DDRB &=~(1<<PORTB4);
	DDRB &=~(1<<PORTB3);     //0bXXX00XX0= DDRB (Entradas)
	DDRB &=~(1<<PORTB0);
	DDRD &=~(1<<PORTD7);	//0b0XXXXXXXX = DDRD (Entradas)
}

uint8_t KEYPAD_Charat(uint8 i, uint8 j) {
	static uint8_t teclado[4][4] = { {'1','2','3','A'},
								     {'4','5','6','B'},
								     {'7','8','9','C'}, 
								     {'*','0','#','D'}}; // Vector con caracteres correspondientes
	return teclado[i][j]; // Devuelve el caracter en la posicion del vector pasada como parametro
}

uint8 KEYPAD_Scan(uint8_t *key) {
	static uint8 i, j; // indices
	for (i = 0; i < 4; i++){ // Para cada fila
		activarFila(i);       // Coloca el bit de la fila i en 0
		for (j = 0; j < 4; j++){ // Para cada columna chequea 1 por 1 si alguna se puso en 0, de ser asi, el boton i,j se presiono.
			if(leerColumna(j)){
				*key=KEYPAD_Charat(i,j);
				desactivarFila(i);        //Coloco el bit de la fila i en 1 nuevamente.
				return 1;
			}
		}
		desactivarFila(i);      //Coloco el bit de la fila i en 1 nuevamente.
	}
	return 0; // Si no se detecto ningun bit de columna en 0
}

void activarFila (uint8 i){
	switch (i){
		case 0:
		//PB4
		DDRB |= (1<<PORTB4);	//0bXXX1XXXX = DDRB (Salidas)
		//PORTB = PORTB & (~(1<<PORTB4)); // Establezco el bit de la fila en 0
		break;
		case 1:
		//PB3
		DDRB |= (1<<PORTB3);	//0bXXXX1XXX = DDRB (Salidas)
		//PORTB = PORTB & (~(1<<PORTB3)); // Establezco el bit de la fila en 0
		break;
		case 2:
		//PB0:
		DDRB |= (1<<PORTB0);	//0bXXXXXXX1 = DDRB (Salidas)
		//PORTB = PORTB & (~(1<<PORTB0)); // Establezco el bit de la fila en 0
		break;
		 case 3:
		//PD7
		DDRD |= (1<<PORTD7);     //0b1XXXXXXX   = DDRD (Salida)
		//PORTD = PORTD & (~(1<<PORTD7)); // Establezco el bit de la fila en 0
		break;
	}
}

void desactivarFila (uint8 i){
	switch (i){
		case 0:
		//PB4
		DDRB &=~(1<<PORTB4);
		//PORTB |= (1<<PORTB4); // Establezco el bit de la fila en 1
		break;
		case 1:
		//PB3
		DDRB &=~(1<<PORTB3);
		//PORTB |= (1<<PORTB3); // Establezco el bit de la fila en 1
		break;
		case 2:
		//PB0:
		DDRB &=~(1<<PORTB0);
		//PORTB |= (1<<PORTB0); // Establezco el bit de la fila en 1
		break;
		case 3:
		//PD7
		DDRD &=~(1<<PORTD7);
		//PORTD |= (1<<PORTD7); // Establezco el bit de la fila en 1
		break;
	}
}

uint8 leerColumna (uint8 j){
	switch(j){
		case 0:
		//PD3
		if ((PIND & (1<<PIND3)) == 0) {  //si el PIND2 esta en 0 retorna verdadero.
			return 1;	
		}
		else
		 return 0;
		break;
		case 1:
		//PD5
		if ((PIND & (1<<PIND5)) == 0) {
			return 1;
		}
		else
		 return 0;
		break;
		case 2:
		//PD4
		if ((PIND & (1<<PIND4)) == 0){
			return 1;
		}
		else
		 return 0;
		break;
		case 3:
		//PD2
		if ((PIND & (1<<PIND2)) == 0){
			return 1;
		}
		else
		 return 0;
		break;
		default:
		 return 0;
		 break;
	}
}
