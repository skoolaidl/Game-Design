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
    
}


void GameLogic::update(float time) {
    if (gameState == 1) {
        //perform game logic  
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