/*
 * mef.h
 *
 * Created: 9/5/2022 14:25:56
 *  Author: Barcala
 */ 


#ifndef MEF_H_
#define MEF_H_
#include "main.h"
typedef enum {DEFECTO, MOD_ANIO, MOD_MES, MOD_DIA, MOD_HORA, MOD_MINUTO, MOD_SEGUNDO, GUARDAR} estados;
typedef unsigned char uint8;
typedef unsigned char uint8_t;

void MEF_init (void);
void Actualizar_Estado(void);
char MEF_get_tecla(void);
void MEF_get_hora (void);
char bisiesto(time t);
void MEF_set_cambio (time aux, uint8 x, uint8 y);




#endif /* MEF_H_ */