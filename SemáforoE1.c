#include <16F877A.h>
#fuses XT,NOWDT,NOPUT,NODEBUG,NOPROTECT,NOBROWNOUT,NOLVP,NOCPD,NOWRT
#use Delay(Clock=4M)     
#use i2c (SLAVE, SDA= PIN_C4, FAST, SCL= PIN_C3, ADDRESS = 0XA0, NOFORCE_SW) //Utilizar la comunicaci�n I2C
#include <lcd.c>		//Librer�a de LCD
int aux=0;			//Usada como bandera para tener control de la acci�n de la interrupci�n
#INT_EXT         //Bloque en cruce                        
void intext_isr() 
{
	if(aux==0)
	{
		aux=1;
		output_high(PIN_B1);	//Encender led para comprobar que se oprimi� el bot�n
		output_high(PIN_B2);	//Mandar la se�al al maestro de que hay bloqueo en cruce para que el MAESTRO mande la instrucci�n 3 a cada ESCLAVO
	}
	else
	{
		aux=0;
		output_low(PIN_B1);		//Apagar led
		output_low(PIN_B2);		//Mandar se�al de que ya no est� obstruido el cruce
	}
}

void main() 
{
	int x;								//variable utilizada para recibir la instrucci�n del maestro
	lcd_init();							//Iniciar la LCD
	delay_ms(6);						//Retardo para que no existan problemas al iniciar la LCD
	Ext_int_edge(L_TO_H);				//Interrupci�n ocurra de bajo a alto
	ENABLE_INTERRUPTS(GLOBAL|INT_EXT);	//Habilitar interrupci�n externa, se usa el pin B0
	set_tris_b(0b00000001);				//Habilitar pin B0 como entrada y los pines B1(LED) y B2 (bloqueo) como salidas
	output_low(PIN_B1);					//Iniciar el LED y obstrucci�n en bajo
	output_low(PIN_B2);

	while(TRUE)               
	{							//I2C_POLL(): TRUE al recibir dato por buffer. FALSE si no recibe dato
		if(i2c_poll()==1)		//Entra a if cuando I2C_POLL es TRUE (1) adem�s de que se activa la funci�n I2C_READ()
     	{
			x = i2c_read();		//Guarda lo le�do el la variable x
			switch(x)			//Utiliza la variable x para seleccionar uno de los casos
			{
				case 1: lcd_gotoxy(1,1);printf(lcd_putc,"\fModere velocidad"); break;		//Muestra en el LCD la instrucci�n 1
				case 2: lcd_gotoxy(1,1);printf(lcd_putc,"\fCalle mojada");lcd_gotoxy(1,2);printf(lcd_putc,"MAX 25Km/hr"); break;  //Muestra en el LCD la instrucci�n 2, esta es cuando est� mojada la carretera
				case 3: lcd_gotoxy(1,1);printf(lcd_putc,"\fCruce obstruido"); break;		//Muestra en el LCD la instrucci�n 3, esta es cuando est� obstruido el cruce
			}
      	}
	}
}