#include "enemy.h"
#include <string>

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
    stepSize = 100.f;
    getSprite().setPosition(xpos, ypos);
}

void Enemy::init(float x, float y, int color) {
    std::string text = "";
    switch (color) {
        case 0: text = "../res/demon_red_sprite_resized.png"; break;
        case 1: text = "../res/demon_blue_sprite_resized.png"; break;
        case 2: text = "../res/demon_green_sprite_resized.png"; break;
    }
        
    if (!texture.loadFromFile(text))
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
    stepSize = 100.f;
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

bool Enemy::trackPlayer(Player& player, float timeS)
{
    if(player.isInAir())
    {
        velocityX = 0.f;
		return false;
    }
    else if(xpos < player.getSprite().getPosition().x)
    {
        velocityX = stepSize * timeS;
		return true;
    }
    else if(xpos > player.getSprite().getPosition().x)
    {
        velocityX = -1*stepSize * timeS;
		return true;
    }
    else
    {
        velocityX = 0.f;
		return false;
    }
}

void Enemy::shoot()
{

}

Projectile& Enemy::getProjectile() {
	return projectile;
}

bool Enemy::getDirection() {
	return direction;
}

void Enemy::setDirection(bool pDirection) {
	direction = pDirection;
}
