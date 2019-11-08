#ifndef ENEMY_H
#define ENEMY_H
#include "shooter.h"

class Enemy : public Shooter {
    private:
        sf::Texture texture;
        float velocityX;
        float velocityY;
        float xpos;
        float ypos;
    
    public:
        Enemy();
        void init();
        void shoot();
        void setVelocityX(float velX);
        void setVelocityY(float velY);
        void updateMovement();
};

#endif