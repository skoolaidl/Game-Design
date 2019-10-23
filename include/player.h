#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "shooter.h"
#include "platform.h"

class Player : public Shooter {
    private:
        sf::Texture texture;
        float velocityX;
        float velocityY;
        float xpos;
        float ypos;
        float maxJumpHeight;
        bool inAir;
        bool falling;
    
    public:
        Player();
        void init();
        void shoot();
        void setVelocityX(float velX);
        void setVelocityY(float velY);
        void updateMovement();
        bool atMaxJumpHeight();
        void setMaxJumpHeight();
        bool isInAir();
        void setInAir(bool b);
        bool isFalling();
        void setFalling(bool b);
        bool collides(std::vector<Actor> objVector);
};

#endif