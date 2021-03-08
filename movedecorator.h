#ifndef MOVEDECORATOR_H
#define MOVEDECORATOR_H

#include "decorator.h"
#include "config.h"

class MoveDecorator : public Decorator{

public:

    // Constructor
    MoveDecorator(Position* pos, QPixmap* sprite, Config* config, WorldObject* widget);

    // Update position
    void updatePosition(int xChange) override;

private:

    // Attributes
    int velocity;
    int curVelocity;
    int distanceFromEdge;

};

#endif // MOVEDECORATOR_H
