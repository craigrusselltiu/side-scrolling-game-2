#include <cstdlib>
#include "eyecandy.h"

// Constructor
EyeCandy::EyeCandy(Position* pos, QPixmap* sprite, int airPos): WorldObject(pos, sprite), airPos(airPos){
    newRandPos();
}

// Type
std::string EyeCandy::type(){return "eyecandy";}

// Update position with possible reset
void EyeCandy::updatePosition(int xChange){
    // Base change
    pos->moveX(xChange);
    // Double speed of airborne
    if(airPos > 0)
        pos->moveX(xChange);
    // Reset pos
    if(pos->getX() + pos->getWidth() <= 0)
        newRandPos();
}

// RNG new position
void EyeCandy::newRandPos(){
    // X pos
    int rngX = std::rand()%(RES_X);
    pos->setX(RES_X+rngX);
    // Y pos if relevant
    if(airPos > 0){
        int rngY = std::rand()%(RES_Y-airPos-(pos->getHeight()));
        pos->setY(airPos + rngY);
    }
}
