#ifndef EYECANDY_H
#define EYECANDY_H

#include <QPixmap>
#include "position.h"
#include "worldobject.h"

class EyeCandy : public WorldObject{

public:

    // Constructor + type
    EyeCandy(Position* pos, QPixmap* sprite, int airPos);
    std::string type();

    // Update position
    void updatePosition(int xChange);
    void newRandPos();

private:

    // Attribute
    int airPos;

};

#endif // EYECANDY_H
