#include "worldmanager.h"
#include "define.h"

// Constructor
WorldManager::WorldManager(Config* config){

    // Store world velocity
    velocity = config->getVelocity();
    totalObstacles = config->getObstacleSequence().size();
    obstacleDistance = config->getObstacleDistance();
    stage = config->getStage();
    testMode = config->getTestMode();

    // Build world objects
    factory = new WorldObjectFactory(config);
    int backgroundPanels = factory->numberBackgroundPanels();
    for(int i = 0; i < backgroundPanels; i++)
        worldObjects.push_back(factory->newWorldObject(WorldObjects::Background, i));
    for(unsigned int i = 0; i < config->getAirCandyTextures().size(); i++)
        worldObjects.push_back(factory->newWorldObject(WorldObjects::AirCandy, i));
    for(unsigned int i = 0; i < config->getGroundCandyTextures().size(); i++)
        worldObjects.push_back(factory->newWorldObject(WorldObjects::GroundCandy, i));
    pausedSprite = new QPixmap(config->getPauseTexture().c_str());
    gameOverSprite = new QPixmap(config->getGameOverTexture().c_str());

}

// Destructor
WorldManager::~WorldManager(){
   for(unsigned int i = 0; i < worldObjects.size(); i++)
       delete worldObjects[i];
   delete factory;
   delete pausedSprite;
}

// Update gamestate - move and draw all objects
void WorldManager::update(QPainter& painter){
    for(unsigned int i = 0; i < worldObjects.size(); i++)
        worldObjects[i]->render(painter);
    if(!paused && !gameOver){
        if(stage >= 2) updateObstacles();
        for(unsigned int i = 0; i < worldObjects.size(); i++){
            worldObjects[i]->updatePosition(-velocity);
        }
    }
    else if(paused){
        painter.drawPixmap(0,0,RES_X,RES_Y, *pausedSprite);
    }
    else{
        if(testMode){
            painter.drawPixmap(0,0,RES_X,RES_Y, *gameOverSprite);
            qDebug() << "Test complete.";
            testMode = false;
        }
    }
}

// Adds or removes obstacles when necessary
void WorldManager::updateObstacles(){
    if(obstacle == -1){
        obstacle = 0;
        addNextObstacle();
    }
    while(worldObjects.back()->passedDistance(obstacleDistance) == 1){
        addNextObstacle();
    }

    // Deletes obstacles when going off screen
    for (auto i = begin(worldObjects); i != end(worldObjects);) {
        WorldObject* current = *i;
        if (current->type()=="obstacle" && current->passedDistance(0)==-1){
            i = worldObjects.erase(i);
            delete current;
        }
        else ++i;
    }
}

// Adds the next obstacle
void WorldManager::addNextObstacle(){
    worldObjects.push_back(factory->newWorldObject(WorldObjects::Obstacle, obstacle));
    obstacle += 1;
    if(obstacle >= totalObstacles){
        obstacle = 0;
    }
}

// Checks if the player has collided with any obstacles
void WorldManager::checkCollision(Player* player){
    std::vector<int> info = player->info();
    QRect playerHitbox(QPoint(info[0],info[1]+info[3]),QPoint(info[0]+info[2],info[1]));

    for (auto i = begin(worldObjects); i != end(worldObjects); i++) {
        WorldObject* current = *i;
        if (current->type()=="obstacle" || current->type()=="decorator"){
            bool collided = current->collided(playerHitbox);
            if(collided && !gameOver){
                player->togglePause();
                gameOver = true;
            }
        }
    }
}

// Toggle paused state
void WorldManager::togglePause(){paused = !paused;}

// Returns true if game over
bool WorldManager::isOver(){return gameOver;}
