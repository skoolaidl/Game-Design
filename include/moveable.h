#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "actor.h"

class Moveable : public Actor {
    
    public:
        virtual void updateMovement(float timeS) = 0;
        

};

#endif