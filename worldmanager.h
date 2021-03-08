#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <QPainter>
#include <vector>
#include "worldobjectfactory.h"
#include "player.h"

class WorldManager {

public:

    // Constructor + Destructor
    WorldManager(Config* config);
    ~WorldManager();

    // Process new frame
    void update(QPainter& painter);

    // Toggle between paused and unpaused
    void togglePause();

    // Adds and removes obstacles when necessary
    void updateObstacles();
    void addNextObstacle();

    // Check collision
    void checkCollision(Player* player);

    // Did player collide
    bool isOver();

private:

    // Attributes
    bool paused = false;
    bool gameOver = false;
    int velocity;
    QPixmap* pausedSprite;
    QPixmap* gameOverSprite;


    // World objects + Factory
    WorldObjectFactory* factory;
    std::vector<WorldObject*> worldObjects;

    // Obstacle counter
    int obstacle = -1;
    int totalObstacles;
    int obstacleDistance;

    int stage;
    bool testMode;
};

#endif // WORLDMANAGER_H
