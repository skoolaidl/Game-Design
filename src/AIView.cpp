#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameLogic.h"
#include "AIView.h"
#include <iostream>

AIView::AIView(GameLogic& logic): View(logic) {}

void AIView::init() {
    gameState = 1;
    drawObjects();
}

void AIView::update(float time) {
    //only active if game is running
    if ( logic.getGameState() == 1 ) {
        //cycle through enemies and make them move, check if they should shoot
    }

void HumanView::drawObjects() {
  
}

}
