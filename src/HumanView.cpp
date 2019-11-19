#include "HumanView.h"
#include "GameLogic.h"
#include <SFML/System.hpp>

/*
HumanView handles the drawing of the game to the screen, user input, and sound
*/

void HumanView::init() {
    left = sf::Keyboard::Left;
    right = sf::Keyboard::Right;
    up = sf::Keyboard::Up;
    shoot = sf::Keyboard::Space;
    waitingForKey = 0;
    sf::Vector2u size = display.getSize();
    width = size.x;
    height = size.y;
    view.reset(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,1.f,1.f));
    if (!texture.loadFromFile("../res/background_resized.gif"))
    {
        // error...
    }
    texture.setRepeated(true);
    background = sf::Sprite(texture);
    background.setTextureRect({ 0, 0, 4000, height});
    //drawObjects();
}

void HumanView::update(float time) {
    
    switch (logic.getGameState()) {
        //error, game not initialized
        case 0: drawMenu(); checkKeyboardStart(); break;
        //running
        case 1: drawObjects(); checkKeyboard(time); break;
        //end of level
        case 2: drawEndLevel(); checkKeyboardEndLevel(); break;
        //settings screen
        case 3: drawSettingsMenu(); checkKeyboardSettings(); break;
        //starting dialogue
        case 4: drawLevelDialogue(); checkKeyboardDialogue(); break;
        //ending dialogue
        case 5: drawEndLevelDialogue(); checkKeyboardDialogue(); break;
        //final ending dialogue
        //final score screen
    }

}

void HumanView::drawMenu() {
    display.clear();
    //load font
    if (!font.loadFromFile("../res/times.ttf"))
    {
        // error...
    }
    sf::Text start("Welcome to Match Made in Hell!\nPress s to go to the settings menu\nPress enter to start", font, 50);
    start.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    start.setFillColor(sf::Color::Red);
    titleText.loadFromFile("../res/title_resized.png");
    sf::Sprite title(titleText);
    display.draw(title);
    display.draw(start);
    display.display();
}

void HumanView::drawSettingsMenu() {
    display.clear();
    //load font
    if (!font.loadFromFile("../res/times.ttf"))
    {
        // error...
    }
    sf::Text settings("Settings Menu\nPress Backspace to return to the main menu\nPress the key you wish to change and then press the key you want\n\n\nThe current keys are:\nMove Right:  \nMove Left:  \nJump:  \nShoot:  ", font, 50);
    settings.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    settings.setFillColor(sf::Color::Red);
    titleText.loadFromFile("../res/title_resized.png");
    sf::Sprite title(titleText);
    display.draw(title);
    display.draw(settings);
    display.display();

}

void HumanView::drawLevelDialogue() {


}

void HumanView::drawEndLevelDialogue() {


}

void HumanView::checkKeyboardSettings() {
    if (waitingForKey > 0) {
        switch (waitingForKey) {
            case 1: right = waitForKeyPress(right); break;
            case 2: left = waitForKeyPress(left); break;
            case 3: up = waitForKeyPress(up); break;
            case 4: shoot = waitForKeyPress(shoot); break;
        }
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        //go back to main menu
        logic.setGameState(0);
    }
    if (sf::Keyboard::isKeyPressed(right)) {
        //assign key for moving right
        waitingForKey = 1;
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        //assign key for moving left
        waitingForKey = 2;
    }
    if (sf::Keyboard::isKeyPressed(up)) {
        //assign key for jumping
        waitingForKey = 3;
    }
    if (sf::Keyboard::isKeyPressed(shoot)) {
        //assign key for shooting
        waitingForKey = 4;
    }
    
}

sf::Keyboard::Key HumanView::waitForKeyPress(sf::Keyboard::Key key) {
    sf::Event Event;
    while (display.pollEvent(Event)) {
        //check for keyPress
        if (Event.type == sf::Event::KeyReleased) {
            waitingForKey = 0;
            return Event.key.code;
        }
    }
    return key;
}

void HumanView::checkKeyboardDialogue() {

}

void HumanView::drawEndLevel() {
    display.clear();
    //load font
    if (!font.loadFromFile("../res/times.ttf"))
    {
        // error...
    }
    sf::Text end("You completed the level", font, 50);
    end.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    end.setFillColor(sf::Color::Red);
    display.draw(end);
    view.setCenter(width/2,height/2);
    display.setView(view);
    display.display();
}

void HumanView::drawObjects() {
    display.clear();
    display.draw(background);
    float x = logic.getPlayer().getSprite().getPosition().x;
    if ( x < width/2 ) {
        x = width/2;
    } 
    
    view.setCenter(x,height/2);
    display.setView(view);
    for(int i = 0; i < logic.getActors().size(); ++i)
    {
        display.draw(logic.getActors()[i].get().getSprite());
    }
    display.draw(logic.getPlayer().getSprite());
    display.display();
}

void HumanView::checkKeyboardStart() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        //set gameState to running
        logic.setGameState(1);   
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //set gameState to settings
        logic.setGameState(3);
    }
}

void HumanView::checkKeyboardEndLevel() {

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
        logic.playerShoot();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        display.close();
    }
}
