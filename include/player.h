#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "moveable.h"
#include "platform.h"
#include "projectile.h"

class Player : public Moveable {
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
        Projectile bullet;
        float bulletOffsetX = 20.f;
        float bulletOffsetY = 15.f;

    public:
        Player();
        void init();
        void setVelocityX(float velX);
        void setVelocityY(float velY);
        void updateMovement();
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
        Projectile& getBullet() { return bullet; }
        float getBulletOffsetX();
        float getBulletOffsetY();
};

#endif
