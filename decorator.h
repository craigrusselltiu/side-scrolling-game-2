#ifndef DECORATOR_H
#define DECORATOR_H

#include <QPixmap>
#include "position.h"
#include "worldobject.h"

class Decorator : public WorldObject{

public:

    // Constructor + type
    Decorator(Position* pos, QPixmap* sprite, WorldObject* widget);
    ~Decorator();
    std::string type();

    // Render decorator
    void render(QPainter& painter) override;

    // Update position
    void updatePosition(int xChange);
    void updatePositionY(int yChange) override;

private:

    // Another decorator/obstacle
    WorldObject* widget;

};

#endif // DECORATOR_H
