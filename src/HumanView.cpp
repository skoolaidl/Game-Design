#include "HumanView.h"
#include "GameLogic.h"
#include <SFML/System.hpp>
#include <string>

/*
HumanView handles the drawing of the game to the screen, user input, and sound
*/

void HumanView::init() {
    currentLevel = 0;
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
    sf::Text start(strings.getString("MenuText"), font, 50);
    start.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    start.setFillColor(sf::Color::Red);
    sf::Text current(strings.getString("CurrentLevel") + std::to_string(currentLevel) + strings.getString("ChangeLevel"), font, 40);
    current.setPosition(display.getSize().x / 2, display.getSize().y / 8);
    current.setFillColor(sf::Color::Red);
    titleText.loadFromFile("../res/title_resized.png");
    sf::Sprite title(titleText);
    display.draw(current);
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
    sf::Text settings(strings.getString("SettingsText"), font, 30);
    settings.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    settings.setFillColor(sf::Color::Red);
    sf::Text keys(strings.getString("CurrentKeys") + strings.getString("MoveRight") + strings.getKey(right) + 
                        "\n" + strings.getString("MoveLeft") + strings.getKey(left) + "\n" 
                        + strings.getString("Jump") + strings.getKey(up) + "\n" 
                        + strings.getString("Shoot") + strings.getKey(shoot), font, 30);
    keys.setPosition(display.getSize().x / 2, display.getSize().y / 8);
    keys.setFillColor(sf::Color::Red);
    titleText.loadFromFile("../res/title_resized.png");
    sf::Sprite title(titleText);
    display.draw(keys);
    display.draw(title);
    display.draw(settings);
    display.display();

}

void HumanView::drawLevelDialogue() {


}

void HumanView::drawEndLevelDialogue() {


}

void HumanView::checkKeyboardSettings() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        //go back to main menu
        logic.setGameState(0);
    }
    
}

void HumanView::checkKeyPressed(sf::Keyboard::Key key) {
    if (logic.getGameState() == 3 && waitingForKey == 0) {
        if (key == sf::Keyboard::Right) {
            waitingForKey = 1;
        }
        if (key == sf::Keyboard::Left) {
            waitingForKey = 2;
        }
        if (key == sf::Keyboard::Up) {
            waitingForKey = 3;
        }
        if (key == sf::Keyboard::Space) {
            waitingForKey = 4;
        }
    }
    else if (waitingForKey > 0) {
        switch (waitingForKey) {
            case 1: right = key; break;
            case 2: left = key; break;
            case 3: up = key; break;
            case 4: shoot = key; break;
        }
        waitingForKey = 0;
    }
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
        logic.setLevel(currentLevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //set gameState to settings
        logic.setGameState(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        //change currentLevel to 0
        currentLevel = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        //change currentLevel to 1
        currentLevel = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        //change currentLevel to 2
        currentLevel = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        //change currentLevel to 3
        currentLevel = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        //change currentLevel to 4
        currentLevel = 4;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        //change currentLevel to 5
        currentLevel = 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        //change currentLevel to 6
        currentLevel = 6;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        //change currentLevel to 1
        currentLevel = 7;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        //change currentLevel to 8
        currentLevel = 8;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
        //change currentLevel to 9
        currentLevel = 9;
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
