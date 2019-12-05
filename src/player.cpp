#include "player.h"
#include <vector>

/*
Player class for the main player character which holds information about the player
and the things that the player can do
*/ 
Player::Player() {

}

void Player::init() {
    if (!texture.loadFromFile("../res/Chad_Sprite_Sheet.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return;
    }
    //setSprite(sf::Sprite(texture));
    setAnimatedSprite(AnimatedSprite(sf::seconds(0.2), true, false));

    walkingAnimationRight.setSpriteSheet(texture);
    //walkingAnimationRight.addFrame(sf::IntRect(37,0,37,37));
    walkingAnimationRight.addFrame(sf::IntRect(74,0,37,37));
    walkingAnimationRight.addFrame(sf::IntRect(111,0,37,37));
    walkingAnimationRight.addFrame(sf::IntRect(148,0,37,37));

    walkingAnimationLeft.setSpriteSheet(texture);
    //walkingAnimationLeft.addFrame(sf::IntRect(37,37,37,37));
    walkingAnimationLeft.addFrame(sf::IntRect(74,37,37,37));
    walkingAnimationLeft.addFrame(sf::IntRect(111,37,37,37));
    walkingAnimationLeft.addFrame(sf::IntRect(148,37,37,37));

    stoppedAnimationRight.setSpriteSheet(texture);
    stoppedAnimationRight.addFrame(sf::IntRect(0,0,37,37));

    stoppedAnimationLeft.setSpriteSheet(texture);
    stoppedAnimationLeft.addFrame(sf::IntRect(0,37,37,37));

    currentAnimation = &stoppedAnimationRight;

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
    getAnimatedSprite().setPosition(xpos, ypos);
    setAnimated(true);
    getAnimatedSprite().play(*currentAnimation);
}

void Player::resetPosition() {
    xpos = 200.f;
    ypos = 300.f;
    getAnimatedSprite().setPosition(xpos, ypos);
}

void Player::updateTexture(float velX)
{

    //std::cout << "updating1" << std::endl;

    if(velocityX < velocityX + velX)
    {
        //right
        currentAnimation = &walkingAnimationRight;
        noKeyWasPressed = false;
    }
    else if(velocityX > velocityX + velX)
    {
        //left
        currentAnimation = &walkingAnimationLeft;
        noKeyWasPressed = false;
    }
    getAnimatedSprite().play(*currentAnimation);
}

void Player::setVelocityX(float velX)
{
    updateTexture(velX);
    velocityX = velX;
}

void Player::setVelocityY(float velY)
{
    velocityY = velY;
}

void Player::updateMovement() 
{
    frameTime = frameClock.restart();
    if (noKeyWasPressed)
    {
        if (direction)
        {
            currentAnimation = &stoppedAnimationRight;
        }
        else
        {
            currentAnimation = &stoppedAnimationLeft; 
        }
        getAnimatedSprite().play(*currentAnimation); 
        //getAnimatedSprite().stop();    
    }
    noKeyWasPressed = true;

    getAnimatedSprite().update(frameTime);

    xpos += velocityX;
    ypos += velocityY;
    getAnimatedSprite().setPosition(xpos, ypos);
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

float Player::getBulletOffsetX() {
    if (direction) {
        return bulletOffsetX;
    }
    else {
        return - bulletOffsetX;
    }
}

float Player::getBulletOffsetY() {
    return bulletOffsetY;
}
