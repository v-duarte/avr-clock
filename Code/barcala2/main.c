/*
 * barcala2.c
 *
 * Created: 11/4/2022 14:06:39
 * Author : Barcala
 */ 

#include "main.h"
#include "lcd.h"
#include "keypad.h"
#include "mef.h"

int main(void)
{
	// Inicializar LCD
	LCDinit();
	// inicializar teclado
	KEYPAD_init();
	// inicializar maq de estados y buffers
	MEF_init();
	// configurar timer (10ms tick)
	Timer_init();
	while(1)
	{
		Actualizar_Estado();
	}
	return 0;
}
