#include <18F4550.h>
#fuses XT,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)
#use i2c (MASTER, SDA= PIN_B0, FAST, SCL= PIN_B1,NOFORCE_SW)	//Declarar comunicaci�n I2C
#define SH PIN_A0		//Entrada del sensor de humedad
#define V1 PIN_C5		//Leds verdes sem�foro 1 y sem�foro 3
#define A1 PIN_C6		//Leds amarillos sem�foro 1 y sem�foro 3
#define R1 PIN_C7		//Leds rojos sem�foro 1 y sem�foro 3
#define ob input_state(PIN_C0)		//Recibe la se�al del ESCLAVO 1 de que hay obstrucci�n en el cruce
#define V4 PIN_C1		//Leds Verdes sem�foro 2 y sem�foro 4
#define A4 PIN_C2		//Leds amarillos sem�foro 2 y sem�foro 4
#define R4 PIN_C4		//Leds rojos sem�foro 2 y sem�foro 4
#define S11 input_state(PIN_D0)		//Sensor 1 del sem�foro 1
#define S12 input_state(PIN_D1)		//Sensor 2 del sem�foro 1
#define S21 input_state(PIN_D2)		//Sensor 1 del sem�foro 2
#define S22 input_state(PIN_D3)		//Sensor 2 del sem�foro 2
#define S31 input_state(PIN_D4)		//Sensor 1 del sem�foro 3
#define S32 input_state(PIN_D5)		//Sensor 2 del sem�foro 3
#define S41 input_state(PIN_D6)		//Sensor 1 del sem�foro 4
#define S42 input_state(PIN_D7)		//Sensor 2 del sem�foro 4
#define on output_high		//on es igual a la funci�n que pone salida en alto
#define off output_low		//off es igual a la funci�n que pone salida en bajo

int i,ins=1,aux=0;		//i: variable utilizada para mandar la direcci�n de los ESCLAVOS.  ins: variable utilizada para mandar la instrucci�n a los ESCLAVOS, al inicio es 1 para mandar esa instrucci�n
						//aux: variable utilizada para entrar a un caso donde hay obstrucci�n de cruce y que los sem�foros esten parpadeando en amarillo
void i2c();				//funci�n donde se realiza la comunicaci�n I2C con los esclavos
void instrucciones();	//funci�n donde se checan las entradas del sensor de humedad y de la obstrucci�n mandada por el ESCLAVO 1

void main(void) 
{
	setup_adc_ports(ALL_ANALOG);		//Activar puertos analogos
	setup_adc(ADC_CLOCK_DIV_8);			//Se divide la entrada del reloj del ADC entre 8 
	set_adc_channel(0);					//Activar canal 0 el cual es el PIN_A0 el cual se llama SH
	delay_ms(500);    //Para esperar que los esclavos inicialicen los LCD
	setup_oscillator(OSC_PLL_OFF|OSC_INTRC|OSC_4MHZ);
	set_tris_c(0x01);		//Activar todo el puerto C como salida (ubicaci�n de leds de sem�foro) excepto el PIN_C0 (ob) el cual es la entrada de la obstrucci�n de cruce dada por el ESCLAVO 1
	set_tris_d(0xff);		//Activar puerto D como entrada (ubicaci�n de los sensores de los sem�foros)
	while(1)
	{	//Se toma en cuanta cada caso posible de la obstrucci�n de los sensores para que con ello actuen los sem�foros. Las funciones i2c() e instrucciones() se llaman a lo largo de cada posible caso para mantener las lcds actualizadas
		if((S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0) || (S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==0 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0)) //Todos los carriles llenos
		{
			
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(920);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(650);
			instrucciones();
			off(a1);
			on(r1);
			off(r4);
			on(v4);
			i2c();
			delay_ms(920);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(750);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==1 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==1 && S21==0 && S22==0 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==1 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0)||(S11==0 && S12==0 && S21==0 && S22==0 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)) //Todos los carriles llenos
		{
			
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(920);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			delay_ms(920);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(650);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==0 && S41==1 && S42==0 && aux==0) || (S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)) //Todos los carriles llenos
		{
			
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(920);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			delay_ms(920);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(650);
			off(a4);
			off(r1);
		}
		else if((S11==0 && S12==0 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0) || (S11==1 && S12==0 && S21==1 && S22==1 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==0 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)) //Todos los carriles llenos
		{
			
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(920);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			delay_ms(920);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(650);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==1 && S41==0 && S42==1 && aux==0) || (S11==0 && S12==1 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==1 && S21==0 && S22==1 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==1 && S31==0 && S32==1 && S41==1 && S42==1 && aux==0)) //Todos los carriles llenos
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(920);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			delay_ms(920);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(650);
			off(a4);
			off(r1);
		}
		else if((S11==0 && S12==0 && S21==0 && S22==0 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0)) //Todos los carriles vac�os
		{
			instrucciones();
			on(r1);
			on(r4);
			i2c();
			off(r1);
			off(r4);
		}
		else if((S11==1 && S12==0 && S21==0 && S22==0 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==0 && S12==0 && S21==0 && S22==0 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==1 && S21==0 && S22==0 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0)|| (S11==1 && S12==1 && S21==0 && S22==0 && S31==0 && S32==1 && S41==0 && S42==0 && aux==0)) //Carril 2 y 4 vac�os
		{
			instrucciones();
			on(r4);
			on(v1);
			i2c();
			off(r4);
			off(v1);
		} 
		else if((S11==0 && S12==0 && S21==0 && S22==0 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==0 && S21==0 && S22==0 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==1 && S21==0 && S22==0 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0))//Carril 2 y 4 vac�os
		{
			instrucciones();
			on(r4);
			on(v1);
			i2c();
			off(r4);
			off(v1);
		}
		else if((S11==1 && S12==1 && S21==0 && S22==0 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==0 && S21==0 && S22==0 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0) || (S11==0 && S12==1 && S21==0 && S22==0 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0))//Carril 2 y 4 vac�os
		{
			instrucciones();
			on(r4);
			on(v1);
			i2c();
			off(r4);
			off(v1);
		}
		else if((S11==0 && S12==0 && S21==1 && S22==0 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==0 && S12==0 && S21==0 && S22==0 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0) || (S11==0 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0))//Carriles 1 y 3 vac�os
		{
			instrucciones();
			on(r1);
			on(v4);
			i2c();
			off(r1);
			off(v4);
		}
		else if((S11==0 && S12==0 && S21==0 && S22==0 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0) || (S11==0 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0) || (S11==0 && S12==0 && S21==1 && S22==0 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0))//Carriles 1 y 3 vac�os
		{
			instrucciones();
			on(r1);
			on(v4);
			i2c();
			off(r1);
			off(v4);
		}
		else if((S11==0 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0) || (S11==0 && S12==0 && S21==0 && S22==1 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0) || (S11==0 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==0 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==0 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0))//Carriles 1 y 3 vac�os
		{
			instrucciones();
			on(r1);
			on(v4);
			i2c();
			off(r1);
			off(v4);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==0 && S31==0 && S32==0 && S41==0 && S42==0 && aux==0) || (S11==1 && S12==1 && S21==0 && S22==0 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0) || (S11==0 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0))//Carril 2 y 4 semivac�o
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(200)
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==0 && S12==0 && S21==0 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==0 && S22==0 && S31==1 && S32==0 && S41==1 && S42==0 && aux==0))//Carril 2 y 4 semivac�o
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(200);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0))//Carril 2 y 4 semivac�o
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(500);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==0 && S22==0 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==1 && S41==0 && S42==0 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0))//Carril 2 y 4 semivac�o
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(200);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0))//Carril 2 y 4 semivac�o
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(200);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==0 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==1 && S41==1 && S42==0 && aux==0))
		{
			instrucciones();
			on(R4);
			on(V1);
			i2c();
			delay_ms(2250);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(570);
			off(a1);
			instrucciones();
			on(r1);
			off(r4);
			on(v4);
			i2c();
			//delay_ms(200);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(600);
			off(a4);
			off(r1);
		}
		else if((S11==1 && S12==0 && S21==0 && S22==1 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==0 && S22==0 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==0 && S22==0 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0))//Carril 1 y 3 semivac�o
		{
			instrucciones();
			on(R1);
			on(V4);
			i2c();
			delay_ms(2250);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(570);
			off(a4);
			instrucciones();
			on(r4);
			off(r1);
			on(v1);
			i2c();
			//delay_ms(200);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(600);
			off(a1);
			off(r4);
		}
		else if((S11==1 && S12==1 && S21==1 && S22==1 && S31==0 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==1 && S21==1 && S22==1 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==1 && S31==1 && S32==1 && S41==1 && S42==1 && aux==0))//Carril 1 y 3 semivac�o
		{
			instrucciones();
			on(R1);
			on(V4);
			i2c();
			delay_ms(2250);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(570);
			off(a4);
			instrucciones();
			on(r4);
			off(r1);
			on(v1);
			i2c();
			//delay_ms(200);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(600);
			off(a1);
			off(r4);
		}
		else if((S11==1 && S12==0 && S21==1 && S22==1 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==1 && S31==1 && S32==0 && S41==1 && S42==0 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==1 && S12==0 && S21==1 && S22==1 && S31==0 && S32==0 && S41==1 && S42==0 && aux==0)) //carril 1 y 3 semivac�os
		{
			instrucciones();
			on(R1);
			on(V4);
			i2c();
			delay_ms(2250);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(570);
			off(a4);
			instrucciones();
			on(r4);
			off(r1);
			on(v1);
			i2c();
			//delay_ms(200);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(600);
			off(a1);
			off(r4);
		}
		else if((S11==0 && S12==0 && S21==1 && S22==0 && S31==1 && S32==0 && S41==1 && S42==1 && aux==0)||(S11==0 && S12==0 && S21==1 && S22==1 && S31==1 && S32==0 && S41==0 && S42==0 && aux==0)) //carril 1 y 3 semivac�os
		{
			instrucciones();
			on(R1);
			on(V4);
			i2c();
			delay_ms(2250);
			off(V4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			delay_ms(250);
			on(v4);
			delay_ms(250);
			off(v4);
			on(a4);
			delay_ms(570);
			off(a4);
			instrucciones();
			on(r4);
			off(r1);
			on(v1);
			i2c();
			//delay_ms(200);
			off(V1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			delay_ms(250);
			on(v1);
			delay_ms(250);
			off(v1);
			on(a1);
			delay_ms(600);
			off(a1);
			off(r4);
		}
		else if(aux==1) //Obstrucci�n de cruce
		{
			instrucciones();
			on(a1);
			on(a4);
			i2c();
			instrucciones();
			off(a1);
			off(a4);
			i2c();
		}
		else			//ocurre cuando no hay autos por lo que los sensores no est�n obstruidos y los sem�foros estan parpadeando en rojo
		{
			instrucciones();
			on(r1);
			on(r4);
			i2c();
			off(r1);
			off(r4);
		}
	} 
}
void i2c() //comunicaci�n i2c 
{
	for(i=0b10100000;i<0b11100000;i=i+0b00010000)		//i va aumentando para ir variando la direcci�n y as� mandar la misma instrucci�n a cada ESCLAVO
	{	
		i2c_start(); // Comienza la comunicacion
		i2c_write(i); // Se envia la direccion del esclavo
		i2c_write(ins);//Se env�a la instrucci�n al esclavo
		i2c_stop(); 	//Se detiene la comunicaci�n
		delay_ms(500);	//Retardo para que no ocurran interferencias con la siguiente comunicaci�n
	}
}
void instrucciones() //chequeo de sensor de humedad y de carril obstruido
{
	if(ob==1)		//Carril obstruido
	{
		ins=3;		//cruce obstruido
		aux=1;	//parpadeo amarillo
	}
	else if(read_adc()>153)		//Sensor de humedad, la instrucci�n se activa cuando se manda m�s de un 60% de humedad (3 volts)
	{
		ins=2; //intrucci�n calle mojada
		aux=0;	//para no parpadear en amarillo
	}
	else
	{
		ins=1; //Mensaje modere velocidad
		aux=0;//para no parpadeo en amarillo
	}
}