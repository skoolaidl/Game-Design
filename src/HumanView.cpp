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
    inAir = false;
    floor.init(1.f, 1.5f, 150.f, 350.f);
    platformA.init(0.3f, 0.4f, 450.f, 290.f);
    platforms.push_back(floor);
    platforms.push_back(platformA);
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
    display.draw(floor.getSprite());
    display.draw(platformA.getSprite());
    display.display();
}

void HumanView::checkKeyboard(float time) {
    time = (time < 1.f) ? 1.f : time;
    if (sf::Keyboard::isKeyPressed(right)) {
        //character moves right
        logic.getPlayer().move((5.f * time), 0.f);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        //character moves left
        logic.getPlayer().move((-5.f * time), 0.f);
    }
    if (sf::Keyboard::isKeyPressed(shoot)) {
        //character shoots
    }
    if (sf::Keyboard::isKeyPressed(up)) {
        //character jumps only if he's on the ground
        if(!inAir) {
            inAir = true;
            logic.getPlayer().jump(time);
        }
    }
    if(!(logic.getPlayer().collides(platforms)))
    {
        inAir = true;
        logic.getPlayer().move(0.f, (5.f * time));
    }
    else
    {
        if(inAir)
        {
            inAir = false;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        display.close();
    }
}

