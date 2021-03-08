#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPixmap>
#include "position.h"
#include "worldobject.h"

class Background : public WorldObject {

public:

    // Constructor + type
    Background(Position* pos, QPixmap* sprite);
    std::string type();

    // Update position
    void updatePosition(int xChange);

private:

    // Original position
    int resetPos;

};

#endif // BACKGROUND_H
