#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "moveable.h"
#include "SFML/System.hpp"

class Projectile : public Moveable {
    private:
        const float move_speed = 350.f;
        const float max_distance = 250.f;
        bool direction;
        sf::Texture texture;
        float startX;
        bool isOffScreen;
        
    
    public:
        Projectile();
        
        void init(int type, float x, float y, bool pDirection);       
        void updateMovement(float timeS);
        bool checkDistance();
        void setOffScreen();
        
};

#endif