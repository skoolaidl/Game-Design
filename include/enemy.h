#ifndef ENEMY_H
#define ENEMY_H
#include "shooter.h"

class Enemy : public Shooter {
public:
    Enemy();
    void init();
    void setPos(sf::vector2f newPos);
    void checkCollision(Bullet bullet);

private:
    sf::Texture enemy;
    float velocityX;
    float velocityY;
    float xpos;
    float ypos;
};

#endif
