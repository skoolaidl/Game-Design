#include "enemy.h"

/*
Basic enemy class that has actions and holds information for the 
created enemy
*/
Enemy::Enemy() {

}

void Enemy::init() {
    if (!texture.loadFromFile("../res/demon_red_sprite_resized.png"))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    velocityX = 0.f;
    velocityY = 0.f;
    xpos = 200.f;
    ypos = 300.f;
    getSprite().setPosition(xpos, ypos);
}

void Enemy::setVelocityX(float velX)
{
    velocityX = velX;
}

void Enemy::setVelocityY(float velY)
{
    velocityY = velY;
}

void Enemy::updateMovement() 
{
    xpos += velocityX;
    ypos += velocityY;
    getSprite().setPosition(xpos, ypos);
    velocityX = 0.f;
    velocityY = 0.f;
}

void Enemy::shoot()
{

}