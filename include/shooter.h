#ifndef SHOOTER_H
#define SHOOTER_H
#include "moveable.h"

class Shooter : public Moveable {
    public:
        virtual void shoot() = 0;
};

#endif