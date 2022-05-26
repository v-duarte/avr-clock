/*
 * clock.c
 *
 * Created: 25/4/2022 15:57:17
 *  Author: Barcala
 */ 
#include "timer.h"
#include "build_defs.h"
volatile time t;
volatile uint8_t FlagLCD_reloj=0;
volatile uint8_t FlagMED_seg=0;
volatile uint8_t contador=0;

void Timer_init(void)
{
	Hora_Default();
	
	TIMSK2 &= ~((1<<TOIE2)|(1<<OCIE2A));					//Desactiva las interrupciones por Overflow y por CTC Match A
	TCNT2 =0;												//Resetea el timer.
	TCCR2A |= (1<<WGM21);									//Activo el modo CTC Match A en timer		
	TCCR2B =(1<<CS20)|(1<<CS21)|(1<<CS22);					//Ajusto el preescalador para tiempo de clock/1024
	OCR2A = 155;											//Cargo OCR = 155 en binario.
	TIMSK2 |= (1<<OCIE2A);									//Activamos la interrupcion en modo CTC Match A en Timer2
	sei();													//Habilitamos las interrupciones				
}

ISR(TIMER2_COMPA_vect)	
{
	if (++contador==100)	
	{
		Actualizar_Hora();
		FlagLCD_reloj=1;
		FlagMED_seg=0;
		contador=0;	
	}
	if (contador==50)
	{
		FlagMED_seg=1;
	}
}

char es_bisiesto(void)      //revisa si es un año bisiesto
{
	if (!(t.year%100))
	{
		return (char)(t.year%400);
	}
	else
	{
		return (char)(t.year%4);
	}
}

uint8_t Check_flagLCD(void){
	return FlagLCD_reloj;
}
uint8_t Check_flagMED_seg(void){
	return FlagMED_seg;
}

void Clock_tick(void){
	if (FlagLCD_reloj){
		FlagLCD_reloj = 0;
	}
	else{
		FlagLCD_reloj = 1;
	}
}

time Clock_hora(void){
	return t;
}

void Actualizar_Hora(void)
{
	if (++t.second==60)        //keep track of time, date, month, and year
	{
		t.second=0;
		if (++t.minute==60)
		{
			t.minute=0;
			if (++t.hour==24)
			{
				t.hour=0;
				if (++t.date==32)
				{
					t.month++;
					t.date=1;
				}
				else if (t.date==31)
				{
					if ((t.month==4) || (t.month==6) || (t.month==9) || (t.month==11))
					{
						t.month++;
						t.date=1;
					}
				}
				else if (t.date==30)
				{
					if(t.month==2)
					{
						t.month++;
						t.date=1;
					}
				}
				else if (t.date==29)
				{
					if((t.month==2) && (es_bisiesto()))
					{
						t.month++;
						t.date=1;
					}
				}
				if (t.month==13)
				{
					t.month=1;
					t.year++;
				}
			}
		}
	}	
}
void TIMER_set_fechahora(time aux)
	{
		t = aux;
	}

void Hora_Default(void){
	//volatile time t={10,29,14,19,4,21}; //10,29,14 => 14:29:10 en LCD y 19,4,21 => 19/04/21 en LCD.
	/*
	t[0] => Segundos.
	t[1] => Minutos.
	t[2] => Hora.
	t[3] => Dia.
	t[4] => Mes.
	t[5] => Año.
	*/
	t.second = BUILD_SEC;
	t.minute = BUILD_MIN;
	t.hour = BUILD_HOUR;
	t.date = BUILD_DATE;
	t.month = BUILD_MONTH;
	t.year = BUILD_YEAR;
}