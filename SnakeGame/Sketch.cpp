#include "ProjectHeader.h"
#include "NokiaLcd.h"
#include "Snake.h"

#include <Arduino.h>
int val0;
int speed=100;
int initspeed=100;
NokiaLcd mylcd;
Snake sarpe(&mylcd);


ISR(BADISR_vect)
{//unhandeled interrupt
}

void isr()
{
	Serial.println("INT");
		noInterrupts();
		val0=analogRead(1);
		//Serial.println(val0);
		if(val0>950)
		{
			//Serial.println("Button 1 pressed");	//button up
			if(sarpe.upp()) direction=up;
		}
		else if(val0>450&&val0<600)
		{
			//Serial.println("Button 2 pressed");	//button down
			if(sarpe.downp())direction=down;
		}
		else if(val0>250&&val0<350)
		{
            if(sarpe.rightp()) direction=right;
		}
		else if(val0>100&&val0<200)
		{
            if(sarpe.leftp())direction=left;
		}
	
}

int freeRam ()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup()
{
    Serial.begin(9600);
	pinMode(2, INPUT);
	attachInterrupt(digitalPinToInterrupt(2), isr,RISING);
}

void loop()
{

   delay(speed); 
    switch (direction)
    {
        
        case up:sarpe.moveUp();break;
        case down:sarpe.moveDown();break;
        case left:sarpe.moveLeft();break;
        case right:sarpe.moveRight();break;
    }
}
