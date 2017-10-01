/*
 * NokiaLcd.cpp
 *
 * Created: 4/16/2016 10:47:14 PM
 *  Author: AOD
 */ 


#include "NokiaLcd.h"
void NokiaLcd::OutMatrix()
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<84;j++)
        {
            LcdWriteData(screenPixels[i][j]);
        }
    }
}
void NokiaLcd::LcdWriteCmd(byte cmd)
{
	digitalWrite(DC,LOW);//DC pin is low for commands
	digitalWrite(CE,LOW);
	shiftOut(DIN,CLK,MSBFIRST,cmd);//transmit serial data
	digitalWrite(CE,HIGH);
}
void NokiaLcd::LcdWriteData(byte dat)
{
	digitalWrite(DC,HIGH);//DC pin is high for commands
	digitalWrite(CE,LOW);
	shiftOut(DIN,CLK,MSBFIRST,dat);//transmit serial data
	digitalWrite(CE,HIGH);
}
void NokiaLcd::LcdWriteChar(char ch)
{
	for(int i=0;i<5;i++) LcdWriteData(pgm_read_byte(&(ASCII[ch-0x20][i]))) ;
	LcdWriteData(0x00);
}
void NokiaLcd::LcdWriteStr(char *str)
{
	for(int i=0;i<strlen(str);i++)  LcdWriteChar(str[i]);
	LcdWriteData(0x00);
}
void NokiaLcd:: AllSegmentsOn()
{
	LcdWriteCmd(0x09);
}
void NokiaLcd:: LcdClear()
{
	for(int i=0;i<504;i++)
	{
		LcdWriteData(0x00);
    }
    memset(screenPixels, 0x00, sizeof(screenPixels));
}
void NokiaLcd:: NormalMode()
{
	LcdWriteCmd(0x0C);
}
void NokiaLcd:: LcdSetXY(byte x,byte y)
{
	LcdWriteCmd(0x80|x);//col
	LcdWriteCmd(0x40|y);//row
}
void NokiaLcd::LcdWritePixel(byte x,byte y)
{/*y position is ranging from 0 to 6 *1byte.I translate the coordinates of the screen for 
  x from 1 to 84 and y from 1 to 48
  */
  byte posy=(y-1)/8;
  LcdSetXY(x-1,posy);
  byte tmp=y%8,pix;
  if(tmp==0)
  {
      pix=128;
  }
  else if(tmp==1)
  {
      pix=1;
  }
  else if(tmp==2)
  {
      pix=2;
  }
  else if(tmp==3)
  {
      pix=4;
  }
  else if(tmp==4)
  {
      pix=8;
  }
  else if(tmp==5)
  {
      pix=16;
  }
  else if(tmp==6)
  {
      pix=32;
  }
  else if(tmp==7)
  {
      pix=64;
  }
  screenPixels[posy][x-1] = (byte)pix |screenPixels[posy][x-1] ;
  LcdWriteData(screenPixels[posy][x-1]);
}
void NokiaLcd::LcdClearPixel(byte x,byte y)
{
    byte posy=(y-1)/8;
    screenPixels[posy][x-1]=0x00;
    LcdSetXY(x-1,posy);
    LcdWriteData(0x00);
}
NokiaLcd::NokiaLcd()
{
    memset(screenPixels, 0x00, sizeof(screenPixels));
	pinMode(RST,OUTPUT);
	pinMode(CE,OUTPUT);
	pinMode(DIN,OUTPUT);
	pinMode(CLK,OUTPUT);
	pinMode(DC,OUTPUT);
	digitalWrite(RST,LOW);
	digitalWrite(RST,HIGH);
	LcdWriteCmd(0x21); //lcd extended commands
	LcdWriteCmd(0xBF);//SET lcd Vop contrast
	LcdWriteCmd(0x04);//set temp coefficient
	LcdWriteCmd(0x14);//lcd bias mode 1:40
	LcdWriteCmd(0x20);//lcd basic commands
	LcdWriteCmd(0x08);//clear
	NormalMode();
	LcdClear();
}
