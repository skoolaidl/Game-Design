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
        float stepSizeX;
        float stepSizeY;
        //true is facing right, false is left
        bool direction;
        void updateTexture(float velX);
    public:
        Player();
        void init();
        void shoot();
        void setVelocityX(float velX);
        void setVelocityY(float velY);
        void updateMovement(float timeS);
        bool atMaxJumpHeight();
        void setMaxJumpHeight();
        bool isInAir();
        void setInAir(bool b);
        bool isFalling();
        void setFalling(bool b);
        void resetPosition();
        float getStepSizeX();
        float getStepSizeY();
        bool getDirection();
        void setDirection(bool pDirection);
};

#endif
