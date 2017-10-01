/*
 * CPPFile1.cpp
 *
 * Created: 2/13/2016 6:14:30 PM
 *  Author: Irimescu
 */ 
#include "ProjectHeader.h"

ISR(BADISR_vect)
{//unhandeled interrupt
	lcd.setCursor(0,0);
	lcd.print("Unexpected error");
}