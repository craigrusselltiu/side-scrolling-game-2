#include "worldobject.h"

// Constructors + Destructors
WorldObject::WorldObject(Position *pos, QPixmap *sprite): pos(pos), sprite(sprite){}
WorldObject::~WorldObject(){delete pos;}

// Render method
void WorldObject::render(QPainter& painter){
    painter.drawPixmap(pos->getX(), pos->getY(), pos->getWidth(), pos->getHeight(), *sprite);
}

// Update Y position
void WorldObject::updatePositionY(int yChange){
    pos->moveY(yChange);
}

// Returns true if the object has passed the configurable distance set
int WorldObject::passedDistance(int obstacleDistance){
    if(pos->getX()+pos->getWidth()<=0) return -1;
    if(pos->getWidth()+pos->getX()+obstacleDistance <= RES_X) return 1;
    return 0;
}

// Returns true if hitboxes intersect
bool WorldObject::collided(QRect playerHitbox){
    QRect obstacleHitbox(QPoint(pos->getX(),pos->getY()+pos->getHeight()),
                         QPoint(pos->getX()+pos->getWidth(),pos->getY()));
    return obstacleHitbox.intersects(playerHitbox);
}
