#include "HumanView.h"
#include "GameLogic.h"
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h> 

/*
HumanView handles the drawing of the game to the screen, user input, and sound
*/

void HumanView::init() {
    srand(time(NULL));
    currentLevel = 0;
    levelsWon = 0;
    left = sf::Keyboard::Left;
    right = sf::Keyboard::Right;
    up = sf::Keyboard::Up;
    shoot = sf::Keyboard::Space;
    waitingForKey = 0;
    first = true;
    sf::Vector2u size = display.getSize();
    width = size.x;
    height = size.y;
    dialogueStage = 0;
    view.reset(sf::FloatRect(0,0,width,height));
    view.setViewport(sf::FloatRect(0,0,1.f,1.f));
    if (!texture.loadFromFile("../res/background_resized.gif"))
    {
        // error...
    }
    texture.setRepeated(true);
    background = sf::Sprite(texture);
    background.setTextureRect({ 0, 0, 4000, height});
    //load font
    if (!font.loadFromFile("../res/times.ttf"))
    {
        // error...
    }
    resetPreferencesVector();
    resetEnemyTypesVector();
}

void HumanView::update(float timeS) {
    
    switch (logic.getGameState()) {
        //error, game not initialized
        case 0: drawMenu(); checkKeyboardStart(timeS); break;
        //running
        case 1: drawObjects(); checkKeyboard(timeS); break;
        //end of level
        case 2: if (first) { drawEndLevel(); } checkKeyboardEndLevel(timeS); break;
        //settings screen
        case 3: drawSettingsMenu(); checkKeyboardSettings(); break;
        //starting dialogue
        case 4: if (first) { drawLevelDialogue(); } checkKeyboardDialogue(timeS); break;
        //ending dialogue
        case 5: if (first) { drawEndLevelDialogue(); } checkKeyboardEndDialogue(timeS); break;
        //final score screen
        case 6: if (first) { drawFinalScore(); } checkKeyboardFinal(); break;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        display.close();
    }

}

void HumanView::drawMenu() {
    if (first) {
        currentLevel = 0;
        logic.resetScores();
        first = false;
        left = sf::Keyboard::Left;
        right = sf::Keyboard::Right;
        up = sf::Keyboard::Up;
        shoot = sf::Keyboard::Space;
    }
    display.clear();
    sf::Text start(strings.getString("MenuText"), font, 50);
    start.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    sf::Text current(strings.getString("CurrentLevel") + std::to_string(currentLevel+1) + strings.getString("LoadLevel"), font, 40);	    
    current.setPosition(display.getSize().x / 2, display.getSize().y / 8);
    current.setFillColor(sf::Color::Red);
    start.setFillColor(sf::Color::Red);
    titleTexture.loadFromFile("../res/title_resized.png");
    sf::Sprite title(titleTexture);
    display.draw(current);
    display.draw(title);
    display.draw(start);
    display.display();
}

void HumanView::drawSettingsMenu() {
    display.clear();
    sf::Text settings(strings.getString("SettingsText"), font, 30);
    settings.setPosition(display.getSize().x / 8, display.getSize().y - 200);
    settings.setFillColor(sf::Color::Red);
    sf::Text keys(strings.getString("CurrentKeys") + strings.getString("MoveRight") + strings.getKey(right) + 
                        "\n" + strings.getString("MoveLeft") + strings.getKey(left) + "\n" 
                        + strings.getString("Jump") + strings.getKey(up) + "\n" 
                        + strings.getString("Shoot") + strings.getKey(shoot), font, 30);
    keys.setPosition(display.getSize().x / 2, display.getSize().y / 8);
    keys.setFillColor(sf::Color::Red);
    sf::Sprite title(titleTexture);
    display.draw(keys);
    display.draw(title);
    display.draw(settings);
    display.display();

}

void HumanView::drawDialogueBox(int dir) {
    display.clear();
    chadTexture.loadFromFile("../res/chad.png");
    sf::Sprite chad(chadTexture);
    chad.setScale(1.4f, 1.4f);
    chad.setPosition(20, 375);
    girlTexture.loadFromFile("../res/girl_example_sprite.png");
    sf::Sprite girl(girlTexture);
    girl.setPosition(width - 230, 360);
    if(dir == 0)
    {
        speechBubbleTexture.loadFromFile("../res/speech_bubble_left.png");
    }
    else
    {
        speechBubbleTexture.loadFromFile("../res/speech_bubble_right.png");
    }
    sf::Sprite speechBubble(speechBubbleTexture);
    speechBubble.setScale(0.93f, 0.9f);
    speechBubble.setPosition(80, 30);
    sf::Text instruct(strings.getString("PressEnter"), font, 20);
    instruct.setPosition(width / 3, 210);
    instruct.setFillColor(sf::Color::Black);
    display.draw(girl);
    display.draw(chad);
    display.draw(speechBubble);
    display.draw(instruct);
}

std::string HumanView::removeRandomString(std::vector<std::string>& vec)
{
    int n = rand() % vec.size();
    std::swap(vec[n], vec.back());
    std::string randElement = vec.back();
    vec.pop_back();
    return randElement;
}

int HumanView::removeRandomInt(std::vector<int>& vec)
{
    int n = rand() % vec.size();
    std::swap(vec[n], vec.back());
    int randElement = vec.back();
    vec.pop_back();
    return randElement;
}

void HumanView::drawLevelDialogue() {
    if (dialogueStage > 3) {
        return;
    }
    if (first) {
        //randomize enemies and their preference
        std::string preference = removeRandomString(preferencesVector);
        int type = removeRandomInt(enemyTypesVector);
        preferenceText = strings.getPreference(preference, type); 
        logic.addPreference(preference, type);
        first = false;
    }
    drawDialogueBox(1);
    sf::Text dialogue;
    dialogue.setFont(font);  
    dialogue.setString(preferenceText);
    dialogue.setFillColor(sf::Color::Magenta);
    dialogue.setPosition(width / 8, 40);
    display.draw(dialogue);
    display.display();
}

void HumanView::drawEndLevelDialogue() {
    if (dialogueStage > 1) {
        return;
    }
    view.setCenter(width / 2, height / 2);
    display.setView(view);
    if (first) {
        switch (dialogueStage) {
            //eventually change to be appropriate based on score
            case 0:
                response = (logic.getScore(currentLevel) < logic.getGoalScore(currentLevel)) ? strings.getResponse("DateNo") : strings.getResponse("DateYes");
                drawDialogueBox(1);
                break;
            case 1: 
                response = (logic.getScore(currentLevel) < logic.getGoalScore(currentLevel)) ? strings.getString("ChadRejected") : strings.getResponse("Rejections");
                drawDialogueBox(0);
                break;
        }
        first = false;
    }
    sf::Text dialogue;
    dialogue.setFont(font);
    dialogue.setString(response);
    dialogue.setFillColor(sf::Color::Red);
    dialogue.setPosition(width / 8, 40);
    display.draw(dialogue);
    display.display();

}

void HumanView::checkKeyboardSettings() {
    //in settings menu, only check for backspace key to go back to menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        //go back to main menu
        logic.setGameState(0);
    }
    
}

void HumanView::checkRebindingKeyPressed(sf::Keyboard::Key key) {
    //waitingForKey checks which key should be bound to which action
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
            case 1: if (checkDuplicateKeys(key)) { right = key; }  break;
            case 2: if (checkDuplicateKeys(key)) { left = key; }  break;
            case 3: if (checkDuplicateKeys(key)) { up = key; }  break;
            case 4: if (checkDuplicateKeys(key)) { shoot = key; }  break;
        }
        waitingForKey = 0;
    }
}

bool HumanView::checkDuplicateKeys(sf::Keyboard::Key newKey) {
    return newKey != right && newKey != left && newKey != up && newKey != shoot;
}

void HumanView::checkKeyboardDialogue(float timeS) {
    //advance to next dialogue after 1 second delay and enter is pressed,
    //if last dialogue stage, go to playing state and current level and reset dialogue variables
    if (dialogueStage > 3 ) {
        dialogueStage = 0;
        logic.setGameState(1);
        first = true;
        resetPreferencesVector();
        resetEnemyTypesVector();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currTime - startTime > 1) {
        dialogueStage++;
        first = true;
        startTime = timeS;
        currTime = timeS;
    }
    currTime += timeS;
}

void HumanView::checkKeyboardEndDialogue(float timeS) {
    //advance to next dialogue after 1 second delay and enter is pressed,
    //if last dialogue stage, go to end level screen after enter pressed
    if (dialogueStage > 1) {
        dialogueStage = 0;
        logic.setGameState(2);
        first = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currTime - startTime > 1) {
        dialogueStage++;
        first = true;
        startTime = timeS;
        currTime = timeS;
    }
    currTime += timeS;
}

void HumanView::drawEndLevel() {
    first = false;
    display.clear();
    sf::Text end(strings.getString("EndLevel") + std::to_string(logic.getScore(currentLevel)), font, 50);
    end.setPosition(display.getSize().x / 8, display.getSize().y - 400);
    end.setFillColor(sf::Color::Red);
    display.draw(end);
    view.setCenter(width/2,height/2);
    display.setView(view);
    display.display();
}

void HumanView::drawFinalScore() {
    first = false;
    display.clear();
    sf::Text score;
    score.setFillColor(sf::Color::Red);
    score.setCharacterSize(40);
    score.setFont(font);
    float posY = height / 4;
    unsigned int finalScore = 0;
    for(int i = 0; i < 10; ++i)
    {
        finalScore += logic.getScore(i);
    }
    score.setString(strings.getString("FinalScore") + std::to_string(finalScore));
    score.setPosition(width / 4, posY);
    display.draw(score);
    score.setCharacterSize(30);
    score.setString(strings.getString("Tier"));
    score.setPosition(width / 10, posY + 100);
    display.draw(score);
    score.setCharacterSize(50);
    score.setString(strings.getTier((levelsWon-1)/2));
    score.setPosition(width / 4, posY + 140);
    display.draw(score);
    score.setCharacterSize(20);
    score.setString(strings.getString("FinalInstruct"));
    score.setPosition(width / 5, posY + 400);
    display.draw(score);
    display.display();
}

void HumanView::checkKeyboardFinal() {
    //only options are backspace to go back to menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        logic.setGameState(0);
    }
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

void HumanView::checkKeyboardStart(float timeS) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        //set gameState to levelDialogue
        logic.setGameState(4);
        startTime = timeS;
        currTime = timeS;
        first = true;
        logic.setLevel(currentLevel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //set gameState to settings
        logic.setGameState(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        //set up info from save file
        readSaveFile();
    }
}

void HumanView::readSaveFile() {
    std::ifstream file;
    file.open("../res/save.txt");
    int x;
    if (file.is_open()) {
        file >> x;
        currentLevel = x;
        for (int i = 0; i < 10; i++) {
            file >> x;
            logic.setScore(i, x);
        }
        file >> x;
        levelsWon = x;
        file >> x;
        right = (sf::Keyboard::Key)x;
        file >> x;
        left = (sf::Keyboard::Key)x;
        file >> x;
        up = (sf::Keyboard::Key)x;
        file >> x;
        shoot = (sf::Keyboard::Key)x;
    }
    file.close();
}

void HumanView::writeSaveFile() {
    std::ofstream file("../res/save.txt", std::ios::trunc);
    if (file.is_open()) {
        file << std::to_string(currentLevel) + " ";
        for (int i = 0; i < 10; i++) {
            file << std::to_string(logic.getScore(i)) + " ";            
        }
        file << std::to_string(levelsWon) + " ";
        file << std::to_string(right) + " ";
        file << std::to_string(left) + " ";
        file << std::to_string(up) + " ";
        file << std::to_string(shoot);
    }
    file.close();
}

void HumanView::checkKeyboardEndLevel(float timeS) {
    //after 1 second, advance to next level when enter pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currTime - startTime > 1) {
        logic.setGameState(4);
        currentLevel++;
        startTime = timeS;
        currTime = timeS;
        first = true;
        //if last level, go to final end game state
        if (currentLevel > 9) {
            logic.setGameState(6);
        }
        else {
            writeSaveFile();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        //go back to main menu if backspace pressed
        currentLevel++;
        writeSaveFile();
        first = true;
        logic.setGameState(0);
    }
    currTime += timeS;
}

void HumanView::checkKeyboard(float timeS) {
    if (sf::Keyboard::isKeyPressed(right)) {
        //character moves right
        logic.playerMoveRight(timeS);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        //character moves left
        logic.playerMoveLeft(timeS);
    }

    if (sf::Keyboard::isKeyPressed(up)) {
        //character jumps
        logic.playerJump(timeS);
    }
    else
    {
        //character falls if player has already let go of up key but does nothing if he is on the ground
        logic.playerFall(timeS);
    }

    if (sf::Keyboard::isKeyPressed(shoot)) {
        //character shoots
        logic.playerShoot();
    }

}

void HumanView::resetPreferencesVector()
{
    preferencesVector = {"Kill", "Kill", "Ignore", "Ignore"};
}

void HumanView::resetEnemyTypesVector()
{
    enemyTypesVector = {0, 1, 2, 3};
}

