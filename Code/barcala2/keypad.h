#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "main.h"

typedef unsigned char uint8;
typedef unsigned char uint8_t;

void KEYPAD_init();
uint8_t KEYPAD_Charat(uint8 i, uint8 j);
uint8 KEYPAD_Scan(uint8_t *key);
void activarFila (uint8 i);
void desactivarFila (uint8 i);
uint8 leerColumna (uint8 j);

#endif
