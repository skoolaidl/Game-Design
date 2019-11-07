#include "GameLogic.h"
#include <iostream>

/*
GameLogic class that holds all of the game objects and detects collisions
and updates game status
*/

GameLogic::GameLogic() {

}

void GameLogic::init(int wWidth, int wHeight) {
    width = wWidth;
    height = wHeight;
    bulletSpeed = 500;
    gravity = 3.f;
    gameState = 1;
    player.init();
    floor.init(1.f, 1.5f, 150.f, 350.f);
    platformA.init(0.3f, 0.4f, 450.f, 280.f);
    actorsVector.push_back(floor);
    actorsVector.push_back(platformA);
}


void GameLogic::update(float time) {
    if (gameState == 1) {
        //perform game logic
        updatePlayerCollision(actorsVector, time);
        player.updateMovement();
    }

}

void GameLogic::softReset() {
    //return player character to beginning of level
}

void GameLogic::reset() {
    //restart level? or restart game?
}

int GameLogic::getGameState() {
    //gameState can be 0, uninitialized; 1, running; or others
    return gameState;
}

void GameLogic::increaseScore(int level, int increase) {
    level--;
    if ( level >= 0 && level <= 9 ) {
        scores[level] = scores[level] + increase;
    }
    else {
        //invalid level
    }
}

Player& GameLogic::getPlayer() {
    return player;
}

std::vector<Actor>& GameLogic::getActors() {
    return actorsVector;
}

bool GameLogic::collides(Actor actor, std::vector<Actor> objVector)
{
    for(int i = 0; i < objVector.size(); ++i)
    {
        if (actor.getSprite().getGlobalBounds().intersects( objVector[i].getSprite().getGlobalBounds() ) )
        {
            return true;
        }
    }
    return false;
}

void GameLogic::updatePlayerCollision(std::vector<Actor> objVector, float time)
{
    float playerX = player.getSprite().getPosition().x;
    float playerY = player.getSprite().getPosition().y;
    float playerWidth = player.getSprite().getGlobalBounds().width;
    float playerHeight = player.getSprite().getGlobalBounds().height;
    float bufferSpaceY = gravity * time;
    float bufferSpaceX = 2.f * time;
    sf::FloatRect topHitBox = sf::FloatRect(playerX, playerY, playerWidth, bufferSpaceY);
    sf::FloatRect bottomHitBox = sf::FloatRect(playerX, playerY + playerHeight - bufferSpaceY, playerWidth, bufferSpaceY);
    //left and right hit boxes are slightly in front (or behind) character sprite to detect objects
    //does not reach all the way to the ground to avoid collision when standing on a platform
    sf::FloatRect leftHitBox = sf::FloatRect(playerX - bufferSpaceX, playerY, bufferSpaceX, playerHeight - 2*bufferSpaceY);
    sf::FloatRect rightHitBox = sf::FloatRect(playerX + playerWidth, playerY, bufferSpaceX, playerHeight - 2*bufferSpaceY);

    for(int i = 0; i < objVector.size(); ++i)
    {
        if (bottomHitBox.intersects( objVector[i].getSprite().getGlobalBounds() ) )
        {
            //player on platform
            player.setFalling(false);
            player.setInAir(false);
            player.setMaxJumpHeight();
        }
        else if (topHitBox.intersects( objVector[i].getSprite().getGlobalBounds() ) )
        {
            //player hit his head while jumping
            player.setFalling(true);
            player.setInAir(true);
        }

        if (leftHitBox.intersects( objVector[i].getSprite().getGlobalBounds() )
                || rightHitBox.intersects( objVector[i].getSprite().getGlobalBounds() ))
        {
            //player running into object on horizontal axis
            player.setVelocityX(0.f);
        }
    }
    //if player is not colliding with any other object, he is in the air
    if(!(collides(player, objVector)))
    {
        player.setInAir(true);
    }
}

void GameLogic::playerMoveRight(float time) {
    if (player.isInAir())    //character has less directional control when in the air
    {
        player.setVelocityX(2.f * time);
    }
    else
    {
        player.setVelocityX(4.f * time);
    }
}

void GameLogic::playerMoveLeft(float time) {
    if (player.isInAir())    //character has less directional control when in the air
    {
        player.setVelocityX(-2.f * time);
    }
    else
    {
        player.setVelocityX(-4.f * time);
    }
}

void GameLogic::playerJump(float time) {
    //character jumps only if he's on the ground or is in the middle of jumping up
    if (!player.atMaxJumpHeight() && !player.isFalling())
    {
        player.setVelocityY(-5.f * time);
    }
    else
    {
        playerFall(time);
    }

}

void GameLogic::playerFall(float time) {
    if (player.isInAir()) //if player is not going up and not on ground then fall
    {
        player.setFalling(true); //player has already jumped and needs to fall before jumping again
        player.setVelocityY(gravity * time);
    }
}

void GameLogic::playerShoot(float time){
  
}
