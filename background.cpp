#include "background.h"
#include "define.h"

// Constructor
Background::Background(Position* pos, QPixmap* sprite): WorldObject(pos, sprite){
    int numPanels = (RES_X/pos->getWidth()) + 2;
    resetPos = pos->getWidth()*(numPanels-1);
}

// Type
std::string Background::type(){return "background";}

// Update position - reset all the way right once off the screen
void Background::updatePosition(int xChange){
    pos->moveX(xChange);
    int cutoffPos = pos->getX() + pos->getWidth();
    if(cutoffPos <= 0)
        pos->setX(resetPos + cutoffPos);
}
