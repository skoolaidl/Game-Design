#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "actor.h"

class Moveable : public Actor {
    
    public:
        virtual void updateMovement() = 0;
        virtual int getClassType() {return -1;}
        

};

#endif