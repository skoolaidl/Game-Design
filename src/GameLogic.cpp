#include "GameLogic.h"
#include "LevelCreator.cpp"

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
    gameState = 1;
    player.init();

    floor.init(1.f, 1.5f, 150.f, 350.f);
    platformA.init(0.3f, 0.4f, 450.f, 290.f);
    
    actorsVector.push_back(floor);
    actorsVector.push_back(platformA);
    
}


void GameLogic::update(float time) {
    if (gameState == 1) {
        //perform game logic

        //player jumping mechanism checking if colliding with other actor
        if(!(collides(player, actorsVector)))
        {
            player.setInAir(true);
        }
        else
        {
            player.setMaxJumpHeight();  //set new player max jump height based on current y position
            player.setInAir(false);
            player.setFalling(false);
        }
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
        if(actor.getSprite().getGlobalBounds().intersects( objVector[i].getSprite().getGlobalBounds() ))
        {
            return true;
        }
    }
    return false;
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
        player.setVelocityY(3.f * time);
    }
}