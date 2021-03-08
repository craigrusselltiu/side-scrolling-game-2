#include "worldobjectfactory.h"
#include "background.h"
#include "eyecandy.h"
#include "obstacle.h"
#include "define.h"
#include "auradecorator.h"
#include "movedecorator.h"

// Constructor
WorldObjectFactory::WorldObjectFactory(Config* config) : config(config){

    // Get eyecandy positions
    airPos = config->getAirPos();
    groundPos = config->getGroundPos();
    obstacleSizeX = config->getObstacleSizeX();
    obstacleSizeY = config->getObstacleSizeY();

    // Load textures
    backgroundTexture = new QPixmap(config->getBackgroundTexture().c_str());
    for(std::string airTexture : config->getAirCandyTextures())
        airCandyTextures.push_back(new QPixmap(airTexture.c_str()));
    for(std::string groundTexture : config->getGroundCandyTextures())
        groundCandyTextures.push_back(new QPixmap(groundTexture.c_str()));
    for(std::string obstacleTexture : config->getObstacleTextures())
        obstacleTextures.push_back(new QPixmap(obstacleTexture.c_str()));
    auraSprite = new QPixmap(config->getAuraTexture().c_str());
    moveSprite = new QPixmap(config->getMoveTexture().c_str());

    // Get obstacle sequence
    obstacleSequence = config->getObstacleSequence();
    test = config->getTestMode();
}

// Destructor
WorldObjectFactory::~WorldObjectFactory(){
    delete backgroundTexture;
    for(unsigned int i = 0; i < airCandyTextures.size(); i++)
        delete airCandyTextures[i];
    for(unsigned int i = 0; i < groundCandyTextures.size(); i++)
        delete groundCandyTextures[i];
}

// Factory method
WorldObject* WorldObjectFactory::newWorldObject(WorldObjects type, int param){
    if(type == WorldObjects::Background){
        int newWidth = backgroundTexture->width() * (double)(RES_Y / backgroundTexture->height());
        Position* pos = new Position(newWidth*param,0,newWidth,RES_Y);
        return new Background(pos, backgroundTexture);
    }
    else if(type == WorldObjects::AirCandy){
        QPixmap* sprite = airCandyTextures[param];
        Position* pos = new Position(0,airPos,sprite->width(), sprite->height());
        return new EyeCandy(pos, sprite, airPos);
    }
    else if(type == WorldObjects::GroundCandy){
        QPixmap* sprite = groundCandyTextures[param];
        Position* pos = new Position(0,groundPos,sprite->width(), sprite->height());
        return new EyeCandy(pos, sprite, 0);
    }
    else if(type == WorldObjects::Obstacle){

        // Choose randomly between textures
        int random = std::rand() % obstacleTextures.size();
        QPixmap* sprite = obstacleTextures[random];

        // Calculate the distance to center aura to sprite
        int offCenter = obstacleSizeX/4;
        Position* pos = new Position(RES_X+offCenter,obstacleSequence[param],obstacleSizeX,obstacleSizeY);
        Position* auraPos = new Position(RES_X,obstacleSequence[param]-offCenter,obstacleSizeX*1.5,obstacleSizeY*1.5);

        // 20% chance moving, 20% chance aura, 10% chance both
        random = std::rand() % 10;
        if(config->getTestMode()){random = 10;}
        if(random == 0){
            return new MoveDecorator(auraPos, sprite, config, new AuraDecorator(auraPos, auraSprite, new Obstacle(pos, sprite, test)));
        }
        else if(random == 1 || random == 2){
            return new AuraDecorator(auraPos, auraSprite, new Obstacle(pos, sprite, test));
        }
        else if(random == 3 || random == 4){
            return new MoveDecorator(pos, sprite, config, new Obstacle(pos, sprite, test));
        }
        else{return new Obstacle(pos, sprite, test);}
    }
    else
        return nullptr;
}

// Work out number of background panels required
int WorldObjectFactory::numberBackgroundPanels(){
    int newWidth = backgroundTexture->width() * (double)(RES_Y / backgroundTexture->height());
    return (RES_X/newWidth) + 2;
}
