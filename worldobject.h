#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <string>
#include <QPixmap>
#include <QPainter>
#include "position.h"
#include <QDebug>
class WorldObject {

public:

    // Constructors + Destructors + type
    WorldObject(Position* pos, QPixmap* sprite);
    virtual ~WorldObject();
    virtual std::string type() = 0;

    // Update / draw
    virtual void render(QPainter& painter);
    virtual void updatePosition(int xChange) = 0;
    virtual void updatePositionY(int yChange);

    // Returns 1 if next obstacle can be placed, -1 if it needs to be deleted
    int passedDistance(int obstacleDistance);

    // Bool to check if obstacle collided with player
    virtual bool collided(QRect playerHitbox);

protected:

    // Attributes
    Position* pos;
    QPixmap* sprite;

};

#endif // WORLDOBJECT_H
