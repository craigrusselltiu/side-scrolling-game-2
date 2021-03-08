#ifndef AURADECORATOR_H
#define AURADECORATOR_H

#include "decorator.h"

class AuraDecorator : public Decorator{

public:

    // Constructor
    AuraDecorator(Position* pos, QPixmap* sprite, WorldObject* widget);

    // Update position
    void updatePosition(int xChange) override;
    void updatePositionY(int yChange) override;
};

#endif // AURADECORATOR_H
