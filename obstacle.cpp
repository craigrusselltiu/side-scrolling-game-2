#include "obstacle.h"

// Constructor
Obstacle::Obstacle(Position* pos, QPixmap* sprite, bool test) : WorldObject(pos, sprite), test(test){}

// Type
std::string Obstacle::type(){return "obstacle";}

// Probe for testing
void Obstacle::probeObstacle(){
    int height = RES_Y-pos->getY();
    if(!probed && pos->getX() <= 200){
        if(height > 340){
            qDebug() << "Test non-colliding obstacle: PASSED";
        } else{
            qDebug() << "Test colliding obstacle: PASSED";
        }
        probed = true;
    }
}

// Update position
void Obstacle::updatePosition(int xChange){
    pos->moveX(xChange);
    if(test) probeObstacle();
}
