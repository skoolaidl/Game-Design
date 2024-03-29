#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "moveable.h"
#include "platform.h"
#include "projectile.h"
#include "AnimatedSprite.h"

class Player : public Moveable {
    private:
        sf::Texture texture;
        float velocityX;
        float velocityY;
        float xpos;
        float ypos;
        float jumpDistance;
        float maxJumpHeight;
        bool inAir;
        bool falling;
        float stepSizeX;
        float stepSizeY;
        //true is facing right, false is left
        bool direction;
        void updateTexture(float velX);
        int number = 0;
        Projectile bullet;
        float bulletOffsetX = 20.f;
        float bulletOffsetY = 15.f;
        //Animation
        Animation* currentAnimation;
        Animation walkingAnimationRight;
        Animation walkingAnimationLeft;
        Animation stoppedAnimationRight;
        Animation stoppedAnimationLeft;
        bool noKeyWasPressed = true;
        sf::Clock frameClock;
        sf::Time frameTime;

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
