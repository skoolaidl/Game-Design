#include "player.h"
#include <vector>

/*
Player class for the main player character which holds information about the player
and the things that the player can do
*/ 
Player::Player() {

}

void Player::init() {
    if (!texture.loadFromFile("../res/chad_sized.png"))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    velocityX = 0.f;
    velocityY = 0.f;
    xpos = 200.f;
    ypos = 300.f;
    maxJumpHeight = ypos - 150.f;
    inAir = false;
    falling = false;
    stepSizeX = 300.f;
    stepSizeY = 500.f;
    direction = true;
    getSprite().setPosition(xpos, ypos);
}

void Player::resetPosition() {
    xpos = 200.f;
    ypos = 300.f;
    getSprite().setPosition(xpos, ypos);
}

void Player::setVelocityX(float velX)
{
    velocityX = velX;
}

void Player::setVelocityY(float velY)
{
    velocityY = velY;
}

void Player::updateMovement(float timeS) 
{
    xpos += velocityX;
    ypos += velocityY;
    getSprite().setPosition(xpos, ypos);
    velocityX = 0.f;
    velocityY = 0.f;
}

bool Player::atMaxJumpHeight()
{
    if (ypos <= maxJumpHeight)
    {
        falling = true;
    }
    return (ypos <= maxJumpHeight);
}

void Player::setMaxJumpHeight()
{
    maxJumpHeight = ypos - 150.f;
}

bool Player::isInAir()
{
    return inAir;
}

void Player::setInAir(bool b)
{
    inAir = b;
}

bool Player::isFalling()
{
    return falling;
}

void Player::setFalling(bool b)
{
    falling = b;
}

void Player::shoot()
{

}

float Player::getStepSizeX()
{
    return stepSizeX;
}

float Player::getStepSizeY()
{
    return stepSizeY;
}

bool Player::getDirection() {
    return direction;
}

void Player::setDirection(bool pDirection) {
    direction = pDirection;
}
