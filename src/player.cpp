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
    xpos = 400.f;
    ypos = 300.f;
    getSprite().setPosition(xpos, ypos);
}

void Player::move(float distanceX, float distanceY) 
{
    xpos += distanceX;
    ypos += distanceY;
    getSprite().setPosition(xpos, ypos);
}

void Player::jump(float deltaS)
{
    float maxJumpHeight = ypos - 100.f;
    while(ypos > maxJumpHeight)
    {
        ypos -= (0.1f * deltaS);
        getSprite().setPosition(xpos, ypos);
    }
}

void Player::shoot()
{

}

bool Player::collides(std::vector<Actor> objVector)
{
    for(int i = 0; i < objVector.size(); ++i)
    {
        if(getSprite().getGlobalBounds().intersects( objVector[i].getSprite().getGlobalBounds() ))
        {
            return true;
        }
    }
    return false;
}