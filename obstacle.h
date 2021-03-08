#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPixmap>
#include "position.h"
#include "worldobject.h"

class Obstacle : public WorldObject{

public:

    // Constructor + type
    Obstacle(Position* pos, QPixmap* sprite, bool test);
    std::string type();

    // Update position
    void updatePosition(int xChange);

    // Probe for testing
    void probeObstacle();

private:

    bool probed = false;
    bool test = false;

};

#endif // OBSTACLE_H
