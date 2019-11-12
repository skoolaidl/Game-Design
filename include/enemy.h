#ifndef ENEMY_H
#define ENEMY_H
#include "shooter.h"
#include "player.h"
#include "Bullet.h"
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
        
        bool isOffScreen;
    
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
        void updateMovement(float timeS);
        void trackPlayer(Player player, float timeS);
        void trackActor(Actor actor, float timeS);
        void setPos(sf::Vector2f newPos);
        void checkCollision(Bullet bullet);
        void setOffScreen();

};

#endif
