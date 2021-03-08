#include "movedecorator.h"

// Constructor
MoveDecorator::MoveDecorator(Position* pos, QPixmap* sprite, Config* config, WorldObject* widget) : Decorator(pos,sprite,widget){
    velocity = config->getObstacleVelocity();
    distanceFromEdge = config->getObstacleEdgeDistance();
}

// Update position
void MoveDecorator::updatePosition(int xChange){
    Decorator::updatePosition(xChange);
    Decorator::updatePositionY(curVelocity);

    if(pos->getY() < 0){
        pos->setY(distanceFromEdge);
    }

    if(pos->getY() >= RES_Y-distanceFromEdge-pos->getHeight()){
        curVelocity = velocity;
    } else if(pos->getY() <= distanceFromEdge){
        curVelocity = -velocity;
    }
}
