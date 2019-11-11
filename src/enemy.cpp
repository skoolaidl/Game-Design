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
    xpos = 0.f;
    ypos = 0.f;
    startXPos = xpos;
    maxRightDistance = 100.f;
    maxLeftDistance = 100.f;
    stepSize = 1.f;
    getSprite().setPosition(xpos, ypos);
}

void Enemy::init(float x, float y) {
    if (!texture.loadFromFile("../res/demon_red_sprite_resized.png"))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    velocityX = 0.f;
    velocityY = 0.f;
    xpos = x;
    ypos = y;
    startXPos = xpos;
    maxRightDistance = 100.f;
    maxLeftDistance = 100.f;
    stepSize = 1.f;
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

float Enemy::getVelocityX()
{
    return velocityX;
}

float Enemy::getStepSize()
{
    return stepSize;
}

float Enemy::getStartX()
{
    return startXPos;
}

float Enemy::getMaxRightDistance()
{
    return maxRightDistance;
}

float Enemy::getMaxLeftDistance()
{
    return maxLeftDistance;
}

void Enemy::setMaxRightDistance(float dist)
{
    maxRightDistance = dist;
}

void Enemy::setMaxLeftDistance(float dist)
{
    maxLeftDistance = dist;
}

void Enemy::updateMovement() 
{
    checkMaxDistance();
    xpos += velocityX;
    ypos += velocityY;
    getSprite().setPosition(xpos, ypos);
}

void Enemy::checkMaxDistance()
{
    if(xpos + velocityX >= startXPos + maxRightDistance 
        || xpos + velocityX <= startXPos - maxLeftDistance)
    {
        velocityX *= -1;
    }
}

void Enemy::trackActor(Actor actor, float timeS)
{
    if(xpos < actor.getSprite().getPosition().x)
    {
        velocityX = stepSize * timeS;
    }
    else if(xpos > actor.getSprite().getPosition().x)
    {
        velocityX = -1*stepSize * timeS;
    }
    else
    {
        velocityX = 0.f;
    }
}

void Enemy::shoot()
{

}