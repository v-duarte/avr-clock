/*
 * clock.h
 *
 * Created: 25/4/2022 16:01:59
 *  Author: Barcala
 */ 


#ifndef CLOCK_H_
#define CLOCK_H_
//#include "main.h"
typedef struct{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char date;
	unsigned char month;
	unsigned char year;
}time;
#include "main.h" //Necesario para arreglar errores de compilacion debido a la estructura time
typedef unsigned char uint8_t;

void Timer_init(void);
char es_bisiesto(void);
uint8_t Check_flagLCD(void);
uint8_t Check_flagMED_seg(void);
void Clock_tick(void);
time Clock_hora(void);
void Actualizar_Hora(void);
void Hora_Default(void);
void TIMER_set_fechahora(time aux);
#endif /* CLOCK_H_ */