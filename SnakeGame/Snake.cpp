/*
 * Snake.cpp
 *
 * Created: 4/17/2016 3:08:06 PM
 *  Author: AOD
 */ 
#include "Snake.h"
#include <stdlib.h>     /* srand, rand */
#include <util/delay.h>
#include "NokiaLcd.h"
////////////////////////////////////////////////////////////////////////// initializations

Snake::Snake(NokiaLcd *screen)
{
    this->screen=*screen;
	screen->LcdWriteStr("SNAKE V0.001");
    magicX=25;
    magicY=25;
	_delay_ms(500);
	screen->LcdClear();
	makeHead(72,21);
}

void Snake::makeHead(byte x,byte y)
{//create the first segment of the snake,the head.Initialize it in center.
	head=(link)malloc(sizeof(struct node));
	head->xPos=x;
	head->yPos=y;
    head->next=NULL;
    tail=head;
    prevT=tail;
    dir=3;
    addNode();addNode();addNode();addNode();
    drawSnake();
}

void Snake::removeNode()
{
    link tmp=head;
    head=head->next;
    free(tmp);
    tmp=NULL;
}
void Snake::addNode()
{
    if(dir==1)
    {//up
        link tmp=tail;
        prevT=tail;
        tail->next=(link)malloc(sizeof(struct node));
        tail->next->xPos=tmp->xPos;
        tail->next->yPos=tmp->yPos-1;
        tail=tail->next;
        tail->next=NULL;
    }
    else if(dir==2)
    {//down
        link tmp=tail;
        prevT=tail;
        tail->next=(link)malloc(sizeof(struct node));
        tail->next->xPos=tmp->xPos;
        tail->next->yPos=tmp->yPos+1;
        tail=tail->next;
        tail->next=NULL;
    }
    else if(dir==3)
    {//left
        link tmp=tail;
        prevT=tail;
        tail->next=(link)malloc(sizeof(struct node));
        tail->next->xPos=tmp->xPos-1;
        tail->next->yPos=tmp->yPos;
        tail=tail->next;
        tail->next=NULL;
    } 
     else if(dir==4)
     {//right
         link tmp=tail;
         prevT=tail;
         tail->next=(link)malloc(sizeof(struct node));
         tail->next->xPos=tmp->xPos+1;
         tail->next->yPos=tmp->yPos;
         tail=tail->next;
         tail->next=NULL;
     }   
    

}


//////////////////////////////////////////////////////////////////////////DRAWING
void Snake::deleteSnake()
{
    link tmp=head;
    while(tmp!=NULL)
    {
         screen.LcdClearPixel(tmp->xPos,tmp->yPos);
         tmp=tmp->next;
    }
}int ctr=0;

void Snake::drawSnake()
{//draw the snake on screen
    link tmp=head;
    Serial.println(tail->xPos);
    screen.LcdWritePixel(magicX,magicY);
    while(tmp!=NULL)
    {
        screen.LcdWritePixel(tmp->xPos,tmp->yPos);
        tmp=tmp->next;
    }
    checkMagic();
}

////////////////////////////////////////////////////////////////////////// DYNAMICS

void Snake::moveUp()
{
    dir=1;
    deleteSnake();
    prevT=tail;
    tail->next=(link)malloc(sizeof(struct node));
    tail->next->yPos=tail->yPos-1;
    if(tail->next->yPos <= 0) tail->next->yPos=42;
    tail->next->xPos=tail->xPos;
    tail->next->next=NULL;
    tail=tail->next;
    removeNode();
    drawSnake();    
}    

void Snake::moveDown()
{  
    dir=2;
    deleteSnake();
    prevT=tail;
    tail->next=(link)malloc(sizeof(struct node));
    tail->next->yPos=tail->yPos+1;
    if(tail->next->yPos == 48) tail->next->yPos=1;
    tail->next->xPos=tail->xPos;
    tail->next->next=NULL;
    tail=tail->next;
    removeNode();
    drawSnake();
}
void Snake::moveLeft()
{
   dir=3;
   deleteSnake();
   prevT=tail;
   tail->next=(link)malloc(sizeof(struct node));
   tail->next->yPos=tail->yPos;
   tail->next->xPos=tail->xPos-1;
   if(tail->next->xPos <= 0) tail->next->xPos=84;
   tail->next->next=NULL;
   tail=tail->next;
   removeNode();
   drawSnake();
}
void Snake::moveRight()
{
     dir=4;
     deleteSnake();
     prevT=tail;
     tail->next=(link)malloc(sizeof(struct node));
     tail->next->yPos=tail->yPos;
     tail->next->xPos=tail->xPos+1;
     if(tail->next->xPos >= 84) tail->next->xPos=1;
     tail->next->next=NULL;
     tail=tail->next;
     removeNode();
     drawSnake();
     
}

boolean Snake::rightp()
{
    if(prevT->xPos >tail->xPos) return false;
    else return true;
}
boolean Snake::leftp()
{
    if(prevT->xPos <tail->xPos) return false;
    else return true; 
}
boolean Snake::upp()
{
    if(prevT->yPos <tail->yPos) return false;
    else return true;
}
boolean Snake::downp()
{
    if(prevT->yPos >tail->yPos) return false;
    else return true;
}

////////////////////////////////////////////////////////////////////////// MAGIC

void Snake::randomPosition()
{
    srand (rand()%millis()+1);
    magicX=rand()%84+1;//x
    magicY=rand()%42+1;//y
    screen.LcdWritePixel(magicX,magicY);
}

void Snake::checkMagic()
{
    
    if(tail->xPos==magicX && tail->yPos ==magicY)
    {
        screen.LcdClearPixel(magicX,magicY);
        addNode();
        addNode();
        delay(150);
        randomPosition();
    }
    link tmp=head;
    while(tmp!=tail)
    {
        if(tmp->xPos == tail->xPos && tmp->yPos == tail->yPos)
        {
            screen.LcdClear();
            screen.LcdSetXY(20,10);
            screen.LcdWriteStr("You Lost!");
            while(1)
            {
                
            }

            delay(100);
        }
        tmp=tmp->next;
    }
    
}