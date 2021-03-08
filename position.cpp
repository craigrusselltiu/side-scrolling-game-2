#include "position.h"

// Constructor
Position::Position(int x, int y, int width, int height, int screenSize):
    x(x), y(y), width(width), height(height), screenSize(screenSize){}

// Getters
int Position::getX(){return x;}
int Position::getY(){return screenSize - y - height;}
int Position::getWidth(){return width;}
int Position::getHeight(){return height;}

// Change pos
void Position::setX(int newX){x = newX;}
void Position::moveX(int change){x += change;}
void Position::setY(int newY){y = newY;}
void Position::moveY(int change){y += change;}
void Position::resetY(int offset){y = offset;}

// Update dimensions
void Position::updateDimensions(int width, int height){
    this->width = width;
    this->height = height;
}
