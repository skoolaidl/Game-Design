#ifndef ENEMY_H
#define ENEMY_H
#include "moveable.h"
#include "player.h"
#include "projectile.h"
#include <SFML/System.hpp>

class Enemy : public Moveable {
    private:
        sf::Texture texture;
        int type;
        float velocityX;
        float velocityY;
        float xpos;
        float ypos;
        int type;
        float startXPos;
        float maxRightDistance;
        float maxLeftDistance;
        float stepSize;
        void checkMaxDistance();
        Projectile projectile;
        bool isOffScreen;
        bool paused;
        std::string leftTexture;
        std::string rightTexture;
        void updateTexture(float velX);
        bool direction;
        float projectileOffsetX;
        float projectileOffsetY;
        bool killStatus;
    
    public:
        Enemy();
        void init();
        void init(float x, float y, int color=0);
        void setVelocityX(float velX);
        void setVelocityY(float velY);
        float getVelocityX();
        float getStepSize();
        float getStartX();
        float getMaxRightDistance();
        float getMaxLeftDistance();
        void setMaxRightDistance(float dist);
        void setMaxLeftDistance(float dist);
        void updateMovement();
        bool trackPlayer(Player& player, float timeS);
        void setPaused(bool b);
        Projectile& getProjectile();
        bool getDirection();
        void setDirection(bool pDirection);
        float getProjectileOffsetX();
        float getProjectileOffsetY();
<<<<<<< HEAD
        void setTexture();
=======
        int getType();
        void setKillStatus(bool b);
        bool getKillStatus();
>>>>>>> develop

};

#endif
