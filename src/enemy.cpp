#include "enemy.h"
#include <string>
#include <time.h> 
#include <iostream>

/*
Basic enemy class that has actions and holds information for the
created enemy
*/

Enemy::Enemy() {

}

void Enemy::init() {
    leftTexture = "../res/demon_red_sprite_resized_0.png";
    rightTexture = "../res/demon_red_sprite_resized_1.png";
    if (!texture.loadFromFile(leftTexture))
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
    isOffScreen = false;
    paused = false;
}

void Enemy::init(float x, float y, int color) {
    switch (color) {
        case 0: leftTexture = "../res/demon_red_sprite_resized_0.png"; rightTexture = "../res/demon_red_sprite_resized_1.png"; break;
        case 1: leftTexture = "../res/demon_blue_sprite_resized_0.png"; rightTexture = "../res/demon_blue_sprite_resized_1.png"; break;
        case 2: leftTexture = "../res/demon_green_sprite_resized_0.png"; rightTexture = "../res/demon_green_sprite_resized_1.png"; break;
    }
    if (!texture.loadFromFile(leftTexture))
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
    isOffScreen = false;
    paused = false;
}

void Enemy::updateTexture(float velX)
{
    if(velocityX < velocityX + velX && texture.loadFromFile(rightTexture))
    {
        getSprite().setTexture(texture);
    }
    else if(velocityX > velocityX + velX && texture.loadFromFile(leftTexture))
    {
        getSprite().setTexture(texture);
    }
}

void Enemy::setVelocityX(float velX)
{
    updateTexture(velX);
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

void Enemy::updateMovement(float timeS) 
{
    if(isOffScreen) {
        return;
    }
    if(paused) {
        return;
    }
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
        setVelocityX(-1 * velocityX);
    }
}

void Enemy::trackPlayer(Player player, float timeS)
{
    float velX = stepSize * timeS;
    if(player.isInAir() || (xpos > player.getSprite().getPosition().x - velX && xpos < player.getSprite().getPosition().x + velX))
    {
        setPaused(true);
    }
    else if(xpos < player.getSprite().getPosition().x)
    {
        setVelocityX(velX);
    }
    else if(xpos > player.getSprite().getPosition().x)
    {
        setVelocityX(-1 * velX);
    }
    else
    {
        setPaused(true);
    }
}

void Enemy::shoot()
{

}

void Enemy::setOffScreen() {
    getSprite().setPosition(400, 650);
    isOffScreen = true;
}

void Enemy::setPaused(bool b)
{
    paused = b;
}

