#include "decorator.h"

// Constructor + destructor + type
Decorator::Decorator(Position* pos, QPixmap* sprite, WorldObject* widget) : WorldObject(pos, sprite), widget(widget){}
Decorator::~Decorator(){delete widget;}
std::string Decorator::type(){return "decorator";}

// Render decorator and its widget
void Decorator::render(QPainter& painter){
    widget->render(painter);
    painter.drawPixmap(pos->getX(), pos->getY(), pos->getWidth(), pos->getHeight(), *sprite);
}

// Update by delegation
void Decorator::updatePosition(int xChange){
    widget->updatePosition(xChange);
}
void Decorator::updatePositionY(int yChange){
    widget->updatePositionY(yChange);
}
