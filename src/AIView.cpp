#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "AIView.h"
#include <iostream>

//AIView::AIView(GameLogic& logic): View(logic) {}

void AIView::init() {
    gameState = logic.getGameState();
}

void AIView::update(float time) {
    //only active if game is running
    switch ( gameState ) {
        //cycle through enemies and make them move, check if they should shoot
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
    }
    
    
}

