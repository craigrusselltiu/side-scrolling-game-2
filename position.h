#ifndef POSITION_H
#define POSITION_H

#include "define.h"

class Position {

public:

    // Constructor
    Position(int x, int y, int width=0, int height=0, int screenSize=RES_Y);

    // Getters
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    // Change pos
    void setX(int newX);
    void moveX(int change);
    void setY(int newY);
    void moveY(int change);
    void resetY(int offset);

    // Update dimensions
    void updateDimensions(int width, int height);

private:

    // Attributes
    int x;
    int y;
    int width;
    int height;
    int screenSize;

};

#endif // POSITION_H
