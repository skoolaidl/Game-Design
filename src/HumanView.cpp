#include "HumanView.h"
#include <SFML/System.hpp>

/*
HumanView handles the drawing of the game to the screen, user input, and sound
*/

void HumanView::init() {
    gameState = 1;
    left = sf::Keyboard::Left;
    right = sf::Keyboard::Right;
    up = sf::Keyboard::Up;
    shoot = sf::Keyboard::Space;
    sf::Vector2u size = display.getSize();
    width = size.x;
    height = size.y;
    drawObjects();
}

void HumanView::update(float time) {
    
    switch (gameState) {
        //error, game not initialized
        case 0: break;
        //running
        case 1: drawObjects(); checkKeyboard(time); break;
        case 2: break;
        case 3: break;
        case 4: break;
    }
    
}


void HumanView::drawObjects() {
    display.clear();

    display.draw(logic.getPlayer().getSprite());
    for(int i = 0; i < logic.getActors().size(); ++i)
    {
        display.draw(logic.getActors()[i].get().getSprite());
    }
    display.display();
}

void HumanView::checkKeyboard(float time) {
    if (sf::Keyboard::isKeyPressed(right)) {
        //character moves right
        logic.playerMoveRight(time);    
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        //character moves left
        logic.playerMoveLeft(time);
    }
    
    if (sf::Keyboard::isKeyPressed(up)) {
        //character jumps
        logic.playerJump(time);
    }
    else
    {
        //character falls if player has already let go of up key but does nothing if he is on the ground
        logic.playerFall(time);
    }
    
    if (sf::Keyboard::isKeyPressed(shoot)) {
        //character shoots
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        display.close();
    }
}

