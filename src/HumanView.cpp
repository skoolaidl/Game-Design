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
    background.setTextureRect({ 0, 0, 12000, height});
    //load font
    if (!font.loadFromFile("../res/ImperfectaRegular.ttf"))
    {
        // error...
    }
    if (!digitalFont.loadFromFile("../res/digital-7.ttf"))
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
        case 1: drawObjects(); checkKeyboard(timeS); checkPlaySounds(); break;
        //end of level
        case 2: if (first) { drawEndLevel(); } checkKeyboardEndLevel(timeS); break;
        //settings screen
        case 3: drawSettingsMenu(); checkKeyboardSettings(); break;
        //starting dialogue
        case 4: if (first) { drawLevelDialogue(); } checkKeyboardDialogue(timeS); break;
        //ending dialogue
        case 5: if (first) { drawEndLevelDialogue(); } checkKeyboardEndDialogue(timeS); break;
        //final score screen
        case 6: if (first) { drawFinalScore(); } checkKeyboardFinal(timeS); break;
        //credits screen
        case 7: if (first) { drawCredits(); } checkKeyboardCredits(); break;
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

    sf::Text current(strings.getString("CurrentLevel") + std::to_string(currentLevel+1), font, 30);	    
    current.setPosition(280, 510);
    current.setFillColor(sf::Color(112,1,1));

    titleTexture.loadFromFile("../res/TitleLogo_Final.png");
    sf::Sprite title(titleTexture);
    title.setPosition(100,-60);

    optionsTexture.loadFromFile("../res/OptionsText.png");
    sf::Sprite options(optionsTexture);
    options.setPosition(200,210);

    display.draw(options);
    display.draw(current);
    display.draw(title);
    display.display();
}

void HumanView::drawSettingsMenu() {
    display.clear();

    settingsTexture.loadFromFile("../res/Settings_Centered.png");
    sf::Sprite settingsOptions(settingsTexture);
    settingsOptions.setPosition(0,500);

    sf::Text keys(strings.getString("CurrentKeys") + strings.getString("MoveRight") + strings.getKey(right) + 
                        "\n" + strings.getString("MoveLeft") + strings.getKey(left) + "\n" 
                        + strings.getString("Jump") + strings.getKey(up) + "\n" 
                        + strings.getString("Shoot") + strings.getKey(shoot), font, 30);
    keys.setPosition(250, 340);
    keys.setFillColor(sf::Color(112,1,1));
    sf::Sprite title(titleTexture);
    title.setPosition(100,-60);
    display.draw(keys);
    display.draw(title);
    display.draw(settingsOptions);
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
    speechBubble.setScale(0.94f, 0.9f);
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
    if(dialogueStage == -2)
    {
        if(first)
        {
            display.clear();
            sf::Text context(strings.getParagraph("Context"), font, 34);
            context.setFillColor(sf::Color::White);
            sf::FloatRect contextRect = context.getLocalBounds();
            context.setOrigin(contextRect.left + contextRect.width/2.f,
                        contextRect.top  + contextRect.height/2.f);
            context.setPosition(sf::Vector2f(width/2.f, height/2.f));

            sf::Text goodLuckText(strings.getString("GoodLuck"), font, 38);
            goodLuckText.setFillColor(sf::Color::White);
            sf::FloatRect goodLuckRect = goodLuckText.getLocalBounds();
            goodLuckText.setOrigin(goodLuckRect.left + goodLuckRect.width/2.f,
                        goodLuckRect.top  + goodLuckRect.height/2.f);
            goodLuckText.setPosition(sf::Vector2f(width/2.f, context.getGlobalBounds().top + context.getGlobalBounds().height + 30.f));

            display.draw(context);
            display.draw(goodLuckText);
            first = false;
        }
    }
    else if(dialogueStage == -1)
    {
        if(first)
        {
            display.clear();
            sf::Text instructions(strings.getParagraph("Instructions"), font, 30);
            instructions.setFillColor(sf::Color::White);
            sf::FloatRect instructionsRect = instructions.getLocalBounds();
            instructions.setOrigin(instructionsRect.left + instructionsRect.width/2.f,
                        instructionsRect.top  + instructionsRect.height/2.f);
            instructions.setPosition(sf::Vector2f(width/2.f, height/2.f + 40.f));

            sf::Text instructionsTitleText(strings.getString("InstructionsTitle"), font, 36);
            instructionsTitleText.setFillColor(sf::Color::White);
            sf::FloatRect instructionsTitleRect = instructionsTitleText.getLocalBounds();
            instructionsTitleText.setOrigin(instructionsTitleRect.left + instructionsTitleRect.width/2.f,
                        instructionsTitleRect.top  + instructionsTitleRect.height/2.f);
            instructionsTitleText.setPosition(sf::Vector2f(width/2.f, instructions.getGlobalBounds().top - 40.f));

            display.draw(instructionsTitleText);
            display.draw(instructions);
            first = false;
        }
    }
    else
    {
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
    }
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
                drawDialogueBox(1);
                response = (logic.getPlayerFail()) ? strings.getResponse("DateNo") : strings.getResponse("DateYes");
                break;
            case 1:
                drawDialogueBox(0);
                response = (logic.getPlayerFail()) ? strings.getString("ChadRejected") : strings.getResponse("Rejections");
                if(!logic.getPlayerFail())
                {
                    levelsWon++;
                }
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
            case 1: if (checkDuplicateKeys(key)) { right = key; strings.setString("RightKey", strings.getKey(right)); }  break;
            case 2: if (checkDuplicateKeys(key)) { left = key; strings.setString("LeftKey", strings.getKey(left)); }  break;
            case 3: if (checkDuplicateKeys(key)) { up = key; strings.setString("JumpKey", strings.getKey(up)); }  break;
            case 4: if (checkDuplicateKeys(key)) { shoot = key; strings.setString("ShootKey", strings.getKey(shoot)); }  break;
        }
        strings.updateInstructionsString();
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
    sf::Text end;
    end.setFont(font);
    end.setCharacterSize(45);
    if(logic.getPlayerFail())
    {
        end.setString(strings.getString("LostLevel") + std::to_string(logic.getScore(currentLevel)));
    }
    else
    {
        end.setString(strings.getString("WonLevel") + std::to_string(logic.getScore(currentLevel)));
    }
    end.setPosition(display.getSize().x / 12, display.getSize().y - 400);
    end.setFillColor(sf::Color::Red);
    display.draw(end);
    end.setCharacterSize(30);
    if(currentLevel < 4)
    {
        end.setString(strings.getString("EndLevelInstruct"));
    }
    else
    {
        end.setString(strings.getString("PressEnter"));
    }
    
    end.setPosition(width / 5, height/2+100);
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
    for(int i = 0; i < 5; ++i)
    {
        finalScore += logic.getScore(i);
    }
    score.setString(strings.getString("FinalScore") + std::to_string(finalScore));
    score.setPosition(width / 4 + 20, posY);
    display.draw(score);
    score.setCharacterSize(40);
    score.setString(strings.getString("Tier"));
    score.setPosition(width / 12, posY + 100);
    display.draw(score);
    
    sf::Text tierText;
    tierText.setFillColor(sf::Color::Red);
    tierText.setFont(font);
    tierText.setCharacterSize(50);
    tierText.setString(strings.getTier(levelsWon-1));
    sf::FloatRect tierTextRect = tierText.getLocalBounds();
    tierText.setOrigin(tierTextRect.left + tierTextRect.width/2.f,
                tierTextRect.top  + tierTextRect.height/2.f);
    tierText.setPosition(sf::Vector2f(width/2.f, score.getGlobalBounds().top + score.getGlobalBounds().height + 50.f));
    display.draw(tierText);

    score.setCharacterSize(30);
    score.setString(strings.getString("PressEnter"));
    score.setPosition(width / 3, posY + 370);
    display.draw(score);
    display.display();
}

void HumanView::drawCredits() {
    first = false;
    display.clear();
    sf::Text thankYou(strings.getString("ThankYou"), font, 40);
    thankYou.setFillColor(sf::Color::White);
    sf::FloatRect thankYouRect = thankYou.getLocalBounds();
    thankYou.setOrigin(thankYouRect.left + thankYouRect.width/2.f,
                thankYouRect.top  + thankYouRect.height/2.f);
    thankYou.setPosition(sf::Vector2f(width/2.f, height/2.f - 100.f));

    sf::Text credits(strings.getString("Credits"), font, 40);
    credits.setFillColor(sf::Color::White);
    sf::FloatRect creditsRect = credits.getLocalBounds();
    credits.setOrigin(creditsRect.left + creditsRect.width/2.f,
                creditsRect.top  + creditsRect.height/2.f);
    credits.setPosition(sf::Vector2f(width/2.f, thankYou.getGlobalBounds().top + thankYou.getGlobalBounds().height + 100.f));

    sf::Text finalInstruction(strings.getString("FinalInstruct"), font, 30);
    finalInstruction.setFillColor(sf::Color::White);
    sf::FloatRect finalInstructionRect = finalInstruction.getLocalBounds();
    finalInstruction.setOrigin(finalInstructionRect.left + finalInstructionRect.width/2.f,
                finalInstructionRect.top  + finalInstructionRect.height/2.f);
    finalInstruction.setPosition(sf::Vector2f(width/2.f, credits.getGlobalBounds().top + credits.getGlobalBounds().height + 150.f));

    display.draw(thankYou);
    display.draw(credits);
    display.draw(finalInstruction);
    display.display();
}

void HumanView::checkKeyboardFinal(float timeS) {
    //only option is enter to go to credits
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && currTime - startTime > 1) {
        first = true;
        startTime = timeS;
        currTime = timeS;
        logic.setGameState(7);
    }
    currTime += timeS;
}

void HumanView::checkKeyboardCredits() {
    //only option is backspace to go back to menu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
        logic.setGameState(0);
        //game completed, so restart game
        currentLevel = 0;
    }
}

std::string HumanView::formatCountDown(int countDown)
{
    if(countDown / 10 == 0)
    {
        return "00" + std::to_string(countDown);
    }
    else if(countDown / 10 < 10)
    {
        return "0" + std::to_string(countDown);
    }
    else
    {
        return std::to_string(countDown);
    }
    

}

void HumanView::drawObjects() {
    display.clear();
    display.draw(background);
    float x = logic.getPlayer().getAnimatedSprite().getPosition().x;
    if ( x < width/2 ) {
        x = width/2;
    } 
    view.setCenter(x,height/2);
    display.setView(view);
    for(int i = 0; i < logic.getActors().size(); ++i)
    {
        display.draw(logic.getActors()[i].get().getSprite());
    }
    sf::Text timerText("TIME\n " + formatCountDown(logic.getCountDown()), digitalFont, 40);
    timerText.setLineSpacing(1.5f);
    timerText.setPosition((view.getCenter().x + width/2) - timerText.getGlobalBounds().width - 30.f, view.getSize().y / 60);
    timerText.setFillColor(sf::Color::White);
    display.draw(timerText);
    display.draw(logic.getPlayer().getAnimatedSprite());
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
        //displays the context screen if a new playthrough
        if(currentLevel == 0)
        {
            dialogueStage = -2;
        }
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
        for (int i = 0; i < 5; i++) {
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
        for (int i = 0; i < 5; i++) {
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
        logic.setLevel(currentLevel);
        //if last level, go to final end game state
        if (currentLevel > 4) {
            currentLevel--;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        logic.setGameState(4);
        startTime = timeS;
        currTime = timeS;
        first = true;
        logic.setLevel(currentLevel);
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

void HumanView::checkPlaySounds() {
    if (logic.hasPlayerShot()) {
        audio.playSound(1);
        logic.setPlayerShot(false);
    }
    if (logic.hasEnemyShot()) {
        audio.playSound(0);
        logic.setEnemyShot(false);
    }
    if (logic.getPlayerJumping() == 1) {
        audio.playSound(2);
    }
    if (logic.isPlayerHit()) {
        audio.playSound(3);
        logic.setPlayerHit(false);
    }
    if (logic.isEnemyHit()) {
        audio.playSound(4);
        logic.setEnemyHit(false);
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

