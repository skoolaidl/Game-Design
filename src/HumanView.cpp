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
    sf::RectangleShape player (sf::Vector2f(50,100));
    player.setFillColor(sf::Color::Red);
    player.setPosition(width/2, height/2);
    display.draw(player);
    display.display();
}

void HumanView::checkKeyboard(float time) {
    if (sf::Keyboard::isKeyPressed(right)) {
        //character moves right
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        //character moves left
    }
    if (sf::Keyboard::isKeyPressed(shoot)) {
        //character shoots
    }
    if (sf::Keyboard::isKeyPressed(up)) {
        //character jumps
    }
}

