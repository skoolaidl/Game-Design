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
        display.draw(logic.getActors()[i].getSprite());
    }
    display.display();
}

void HumanView::checkKeyboard(float time) {
    time = (time < 1.f) ? 1.f : time;
    if (sf::Keyboard::isKeyPressed(right)) {
        //character moves right
        if (logic.getPlayer().isInAir())    //character has less directional control when in the air
        {
            logic.getPlayer().setVelocityX(2.f * time);
        }
        else
        {
            logic.getPlayer().setVelocityX(4.f * time);
        }        
    }
    else if (sf::Keyboard::isKeyPressed(left)) {
        //character moves left
        if (logic.getPlayer().isInAir())    //character has less directional control when in the air
        {
            logic.getPlayer().setVelocityX(-2.f * time);
        }
        else
        {
            logic.getPlayer().setVelocityX(-4.f * time);
        }      
    }
    else
    {
        logic.getPlayer().setVelocityX(0.f);
    }
    
    if (sf::Keyboard::isKeyPressed(up) && !logic.getPlayer().atMaxJumpHeight() && !logic.getPlayer().isFalling()) {
        //character jumps only if he's on the ground or is in the middle of jumping up
        logic.getPlayer().setVelocityY(-5.f * time);
    }
    else if (logic.getPlayer().isInAir()) //if player is not going up and not on ground then fall
    {
        logic.getPlayer().setFalling(true); //player has already jumped and needs to fall before jumping again
        logic.getPlayer().setVelocityY(3.f * time);
    }
    else
    {
        logic.getPlayer().setVelocityY(0.f);
    }

    logic.getPlayer().updateMovement();
    
    if (sf::Keyboard::isKeyPressed(shoot)) {
        //character shoots
    }

    // if(!(logic.getPlayer().collides(logic.getActors())))
    // {
    //     inAir = true;
    //     logic.getPlayer().move(0.f, (5.f * time));
    // }
    // else
    // {
    //     if(inAir)
    //     {
    //         inAir = false;
    //     }
    // }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        display.close();
    }
}

