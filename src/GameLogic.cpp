#include "GameLogic.h"

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
        if(!(player.collides(actorsVector)))
        {
            player.setInAir(true);
        }
        else
        {
            player.setMaxJumpHeight();  //set new player max jump height based on current y position
            player.setInAir(false);
            player.setFalling(false);
        }
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