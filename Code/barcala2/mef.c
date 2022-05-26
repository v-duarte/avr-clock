/*
 * mef.c
 *
 * Created: 9/5/2022 14:25:40
 *  Author: Barcala
 */ 
#include "mef.h"
#include "timer.h"
#include "lcd.h"
#include "keypad.h"
static estados estado;
uint8_t tecla;
time t;
void MEF_init(void){
	estado = DEFECTO;
}
	
void Actualizar_Estado(void){
	static time aux_t;
		
	switch (estado)
	{
		case DEFECTO:
		{
			MEF_get_hora();			//imprime hora en el display cada 1 segundo
			if (MEF_get_tecla())	//revisa si se presiono la tecla A y cambia de estado
			{ 
				if (tecla == 'A')
				{
				    aux_t.year = t.year;
					aux_t.month = t.month;
					aux_t.date = t.date;
					aux_t.hour = t.hour;
					aux_t.minute = t.minute;
					aux_t.second = t.second;
					estado = MOD_ANIO;
			    }
			}
			break;
		}
		case MOD_ANIO:
		{
			MEF_set_cambio(aux_t, 10, 1);      // Muestra en LCD fecha actual con el año titilando.
			if (MEF_get_tecla())
			{ //revisa si se presiono la tecla A y cambia de estado
				switch (tecla)
				{
					case 'A':
					{
						estado = MOD_MES;
						break;	
					}
					case 'B':
					{
						if (++aux_t.year==100)
						{
							aux_t.year=0;
						}
							
						break;	
					}
					case 'C':
					{
						if (--aux_t.year==255)
							{aux_t.year=99;}
						break;
					}
					case 'D':
					{
						estado = DEFECTO;
						break;
					}	
				}
			}
			break;
		}
		case MOD_MES:
		{
			MEF_set_cambio(aux_t, 7, 1);      // Muestra en LCD fecha actual con el mes titilando.
			if (MEF_get_tecla())			  //revisa si se presiono la tecla A y cambia de estado
			{ 
				switch (tecla)
				{
					case 'A':
					{
						estado = MOD_DIA;
						break;
					}
					case 'B':
					{
						if (++aux_t.month==13)
							{aux_t.month=1;}
						break;
					}
					case 'C':
					{
						if (--aux_t.month==0)
							{aux_t.month=12;}
						break;
					}
					case 'D':
					{
						estado = DEFECTO;
						break;
					}
				}
		   }
			break;
		}
		case MOD_DIA:
			{
				MEF_set_cambio(aux_t, 4, 1);         // Muestra en LCD fecha actual con el dia titilando.
				if (MEF_get_tecla())				 //revisa si se presiono la tecla A y cambia de estado
				{ 
					switch (tecla)
					{
						case 'A':
						estado = MOD_HORA;
						break;
						case 'B':
						{
						if ((aux_t.month==4) || (aux_t.month==6) || (aux_t.month==9) || (aux_t.month==11))
						{
							if (++aux_t.date==31)
							aux_t.date=1;
						}
						else if((aux_t.month==2) && (bisiesto(aux_t)))		//Si no es bisiesto
						{	
							if (++aux_t.date==29)
							aux_t.date=1;
						}
						else if((aux_t.month==2) && !(bisiesto(aux_t)))	//Si es bisiesto
						{
							if (++aux_t.date==30)
							aux_t.date=1;
						}
						else 
						{
							if (++aux_t.date==32)
							aux_t.date=1;
						}
						break;
						}
						case 'C':
						{
						if ((aux_t.month==4) || (aux_t.month==6) || (aux_t.month==9) || (aux_t.month==11))
						{
							if (--aux_t.date==0)
							aux_t.date=30;
						}
						else if((aux_t.month==2) && (bisiesto(aux_t)))	//Si no es bisiesto
						{
							if (--aux_t.date==0)
							aux_t.date=28;
						}
						else if((aux_t.month==2) && !(bisiesto(aux_t)))	//Si es bisiesto
						{
							if (--aux_t.date==0)
							aux_t.date=29;
						}
						else
						{
							if (--aux_t.date==0)
							aux_t.date=31;
						}
						break;
						}
						case 'D':
						estado = DEFECTO;
						break;
					}
				}
			break;
			}
		case MOD_HORA:
		{
			MEF_set_cambio(aux_t, 4, 0);      // Muestra en LCD fecha actual con el mes titilando.
			if (MEF_get_tecla())			 //revisa si se presiono la tecla A y cambia de estado
			{
				switch (tecla)
				{
					case 'A':
					estado = MOD_MINUTO;
					break;
					case 'B':
					if (++aux_t.hour==24)
					aux_t.hour=0;
					break;
					case 'C':
					if (--aux_t.hour==255)
					aux_t.hour=23;
					break;
					case 'D':
					estado = DEFECTO;
					break;
				}
			}
			break;
		}
		case MOD_MINUTO:
			{
				MEF_set_cambio(aux_t, 7, 0);      // Muestra en LCD fecha actual con el mes titilando.
				if (MEF_get_tecla())			 //revisa si se presiono la tecla A y cambia de estado
				{
					switch (tecla)
					{
						case 'A':
						estado = MOD_SEGUNDO;
						break;
						case 'B':
						if (++aux_t.minute==60)
						aux_t.minute=0;
						break;
						case 'C':
						if (--aux_t.minute==255)
						aux_t.minute=59;
						break;
						case 'D':
						estado = DEFECTO;
						break;
					}
				}
				break;
			}
		case MOD_SEGUNDO:
			{
				MEF_set_cambio(aux_t, 10, 0);      // Muestra en LCD fecha actual con el mes titilando.
				if (MEF_get_tecla())			  //revisa si se presiono la tecla A y cambia de estado
				{ 
					switch (tecla)
					{
						case 'A':
						estado = GUARDAR;
						break;
						case 'B':
						if (++aux_t.second==60)
						aux_t.second=0;
						break;
						case 'C':
						if (--aux_t.second==255)
						aux_t.second=59;
						break;
						case 'D':
						estado = DEFECTO;
						break;
					}
				}
				break;
			}
		case GUARDAR:
		{
			TIMER_set_fechahora(aux_t);
			estado = DEFECTO;
			break;
		}
	}
}
char MEF_get_tecla(void){
	if (KEYPAD_Scan(&tecla) == 0)
	{
		return 0;
	}
	_delay_ms(200);
	return 1;

}	

void MEF_get_hora (void){
	if(Check_flagLCD()==1){ //if(FlagLCD==1)
		t = Clock_hora();
		LCDGotoXY(4,0);
		LCDescribeDato(t.hour,2);
		LCDsendChar(':');
		LCDescribeDato(t.minute,2);
		LCDsendChar(':');
		LCDescribeDato(t.second,2);
		LCDGotoXY(4,1);
		LCDescribeDato(t.date,2);
		LCDsendChar('/');
		LCDescribeDato(t.month,2);
		LCDsendChar('/');
		LCDescribeDato(t.year,2);
		Clock_tick();	//FlagLCD=0;
	}
}

void MEF_set_cambio (time aux, uint8 x, uint8 y){
	if(Check_flagMED_seg()==1)
	{
		LCDGotoXY(4,0);
		LCDescribeDato(aux.hour,2);
		LCDsendChar(':');
		LCDescribeDato(aux.minute,2);
		LCDsendChar(':');
		LCDescribeDato(aux.second,2);
		LCDGotoXY(4,1);
		LCDescribeDato(aux.date,2);
		LCDsendChar('/');
		LCDescribeDato(aux.month,2);
		LCDsendChar('/');
		LCDescribeDato(aux.year,2);
	}
	else
	{
		LCDGotoXY(x,y);
		LCDsendChar(' ');
		LCDsendChar(' ');
	}
}
char bisiesto(time t)    
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