#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "moveable.h"
#include "SFML/System.hpp"

class Projectile : public Moveable {
    private:
        float stepSize = 350.f;
        float maxDistance = 200.f;
        float velocity;
        bool direction;
        sf::Texture texture;
        float startX;
        bool isAvailable;
        int type;
        
    public:
        Projectile();
        void init(int pType, float x, float y, bool pDirection);       
        void updateMovement();
        bool checkDistance();
        void setAvailable();
        void setVelocity(float timeS);
        bool getIsAvailable();
        int getType();
        
};

#endif