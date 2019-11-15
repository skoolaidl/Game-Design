#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "moveable.h"
#include "SFML/System.hpp"

class Projectile : public Moveable {
    private:
        const float move_speed = 100.f;
        const float max_distance = 500.f;
		float velocity;
        bool direction;
        sf::Texture texture;
        float startX;
        bool isOffScreen;
        
    
    public:
        Projectile();
        
        void init(int type, float x, float y, bool pDirection);       
        void updateMovement();
        bool checkDistance();
        void setOffScreen();
		void setVelocity(float timeS);
        
};

#endif