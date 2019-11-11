#include "HumanView.h"
#include <SFML/System.hpp>

/*
HumanView handles the drawing of the game to the screen, user input, and sound
*/

void HumanView::init() {
    left = sf::Keyboard::Left;
    right = sf::Keyboard::Right;
    up = sf::Keyboard::Up;
    shoot = sf::Keyboard::Space;
    sf::Vector2u size = display.getSize();
    width = size.x;
    height = size.y;
    view.reset(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,1.f,1.f));
    drawObjects();
}

void HumanView::update(float time) {
    
    switch (logic.getGameState()) {
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
    
    float x = logic.getPlayer().getSprite().getPosition().x;
    if ( x < width/2 ) {
        x = width/2;
    } 
    
    view.setCenter(x,height/2);
    display.setView(view);
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

