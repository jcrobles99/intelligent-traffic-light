#include <16F877A.h>
#fuses XT,NOWDT,NOPUT,NODEBUG,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD,NOWRT
#use Delay(Clock=4M)     
#use i2c (SLAVE, SDA= PIN_C4, FAST, SCL= PIN_C3, ADDRESS = 0XD0, NOFORCE_SW)//Utilizar la comunicaci�n I2C
#include <lcd.c>		//Librer�a de LCD

void main() 
{
	int x;					//variable utilizada para recibir la instrucci�n del maestro
	lcd_init();				//Iniciar la LCD
	delay_ms(6);			//Retardo para que no existan problemas al iniciar la LCD
	while(TRUE)               
	{							//I2C_POLL(): TRUE al recibir dato por buffer. FALSE si no recibe dato
		if(i2c_poll()==1)		//Entra a if cuando I2C_POLL es TRUE (1) adem�s de que se activa la funci�n I2C_READ()
     	{
			x = i2c_read();		//Guarda lo le�do el la variable x
			switch(x)			//Utiliza la variable x para seleccionar uno de los casos
			{
				case 1: lcd_gotoxy(1,1);printf(lcd_putc,"\fModere velocidad"); break;		//Muestra en el LCD la instrucci�n 1
				case 2: lcd_gotoxy(1,1);printf(lcd_putc,"\fCalle mojada");lcd_gotoxy(1,2);printf(lcd_putc,"MAX 25Km/hr"); break; 	//Muestra en el LCD la instrucci�n 2, esta es cuando est� mojada la carretera
				case 3: lcd_gotoxy(1,1);printf(lcd_putc,"\fCruce obstruido"); break;		//Muestra en el LCD la instrucci�n 3, esta es cuando est� obstruido el cruce
			}
			delay_ms(500);
      	}
	}
}