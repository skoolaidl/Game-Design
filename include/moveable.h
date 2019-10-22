#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "actor.h"

class Moveable : public Actor {
    
    public:
        virtual void move(float distanceX, float distanceY) = 0;
        

};

#endif