#include "player.h"
#include "define.h"

// Constructor
Player::Player(Config* config){

    pos = new Position(config->getInitX(), config->getInitY());
    sprite = new QPixmap(config->getPlayerTexture().c_str());
    updateDimensions(config->getSize());

    gravity = config->getGravity();
    jumpVelocity = config->getJumpVelocity();
    initY = pos->getY();
    trueInitY = config->getInitY();
}

// Destructor
Player::~Player(){
    delete pos;
    delete sprite;
}

// Render
void Player::render(QPainter& painter){
    painter.drawPixmap(pos->getX(), pos->getY(), pos->getWidth(), pos->getHeight(), *sprite);
    if(!paused) updatePosition();
}

// Change dimensions
void Player::updateDimensions(std::string size){

    // Calc new dimensions
    int newWidth = sprite->width();
    int newHeight = sprite->height();
    if(size == "tiny"){
        newWidth *= TINY;
        newHeight *= TINY;
    }
    else if(size == "normal"){
        newWidth *= NORMAL;
        newHeight *= NORMAL;
    }
    else if(size == "large"){
        newWidth *= LARGE;
        newHeight *= LARGE;
    }
    else if(size == "giant"){
        newWidth *= GIANT;
        newHeight *= GIANT;
    }
    else{
      return; // Not legit size so dont update
    }

    // Process update
    this->size = size;
    pos->updateDimensions(newWidth, newHeight);
}

// Updates the player's position (due to gravity)
void Player::updatePosition(){
    pos->moveY(yVel);

    if(pos->getY()<initY){
        yVel += gravity / 70.0;
    }
    else if(yVel != 0){
        yVel = 0;
        pos->setY(trueInitY);
        grounded = true;
        doubleJump = false;
    }
}

// Makes the player jump (or double jump if already jumped)
void Player::jump(){
    if(grounded){
        yVel += jumpVelocity;
        grounded = false;
    } else if(!doubleJump){
        yVel = 0;
        yVel += jumpVelocity;
        doubleJump = true;
    }
}

// Returns x, y coordinates, and x, y sizes
std::vector<int> Player::info(){
    std::vector<int> temp;
    temp.push_back(pos->getX());
    temp.push_back(pos->getY());
    temp.push_back(pos->getWidth());
    temp.push_back(pos->getHeight());
    return temp;
}


// Toggle paused state
void Player::togglePause(){paused = !paused;}
