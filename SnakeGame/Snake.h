/*
 * Snake.h
 *
 * Created: 4/17/2016 3:06:56 PM
 *  Author: AOD
 */ 

#ifndef SNAKE_H_
#define SNAKE_H_
#include <Arduino.h>
#include "NokiaLcd.h"
typedef struct node* link;
struct node
{
	link next;
	byte xPos;
	byte yPos;
};
class Snake
{

	private :NokiaLcd screen;
	public:
    link head,tail,prevT;
    byte magicX,magicY,dir;         //what you need to get;
	void makeHead(byte x,byte y);
	void addNode();
    void removeNode();
	Snake(NokiaLcd *screen);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void drawSnake();
    void drawTail();
	void randomPosition();
    boolean rightp();
    boolean leftp();
    boolean upp();
    boolean downp();
    void deleteSnake();
    void checkMagic();
    
};
#endif /* SNAKE_H_ */