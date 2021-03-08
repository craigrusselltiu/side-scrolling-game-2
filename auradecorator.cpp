#include "auradecorator.h"

// Constructor
AuraDecorator::AuraDecorator(Position* pos, QPixmap* sprite, WorldObject* widget) : Decorator(pos,sprite,widget){}

// Update by delegation
void AuraDecorator::updatePosition(int xChange){
    Decorator::updatePosition(xChange);
    pos->moveX(xChange);
}
void AuraDecorator::updatePositionY(int yChange){
    Decorator::updatePositionY(yChange);
    pos->moveY(yChange);
}
