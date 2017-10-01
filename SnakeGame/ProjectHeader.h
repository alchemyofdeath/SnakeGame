/*
 * ProjectHeader.h
 *
 * Created: 2/12/2016 10:06:10 PM
 *  Author: Irimescu
 */ 


#ifndef PROJECTHEADER_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
void setup();
void loop();
void isr();
int freeRam();
enum dir {up,down,left,right,null};
dir direction=null;
unsigned long time=0;

#define PROJECTHEADER_H_
#endif /* PROJECTHEADER_H_ */