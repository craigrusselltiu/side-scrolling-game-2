#ifndef PLAYER_H
#define PLAYER_H

#include <QPainter>
#include <QPixmap>
#include <string>
#include "config.h"
#include "position.h"

class Player{

public:

    // Constructor + Destructor
    Player(Config* config);
    ~Player();

    // Draw
    void render(QPainter& painter);

    // Update size
    void updateDimensions(std::string size);

    // Update movement
    void updatePosition();
    void jump();
    void togglePause();

    // Get info
    std::vector<int> info();

private:

    // Attributes
    Position* pos;
    std::string size;
    QPixmap* sprite;

    double gravity;
    double yVel = 0;
    int jumpVelocity;
    int initY;
    int trueInitY;
    bool grounded = true;
    bool paused = false;
    bool doubleJump = false;

};

#endif // PLAYER_H
