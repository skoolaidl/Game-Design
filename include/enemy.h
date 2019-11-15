#ifndef ENEMY_H
#define ENEMY_H
#include "shooter.h"
#include "player.h"
#include "projectile.h"
#include <SFML/System.hpp>

class Enemy : public Shooter {
    private:
        sf::Texture texture;
        float velocityX;
        float velocityY;
        float xpos;
        float ypos;
        float startXPos;
        float maxRightDistance;
        float maxLeftDistance;
        float stepSize;
        void checkMaxDistance();
		Projectile projectile;
        bool isOffScreen;
		bool direction;
    
    public:
        Enemy();
        void init();
        void init(float x, float y, int color=0);
        void shoot();
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
        bool trackPlayer(Player player, float timeS);
        void setOffScreen();
		Projectile& getProjectile();
		bool getDirection();
		void setDirection(bool pDirection);

};

#endif
