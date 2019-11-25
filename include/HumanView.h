#ifndef HUMANVIEW_H
#define HUMANVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "view.h"
#include "GameLogic.h"
#include "platform.h"
#include "Strings.h"

class HumanView : public View {
    
    private:
        //display window
        sf::RenderWindow& display;
        sf::View& view;
        Strings& strings;
        void drawMenu();
        void checkKeyboard(float time);
        void checkKeyboardStart(float time);
        void checkKeyboardEndLevel(float time);
        void drawEndLevel();
        void drawSettingsMenu();
        void drawLevelDialogue();
        void drawEndLevelDialogue();
        void drawFinalScore();
        void checkKeyboardSettings();
        void checkKeyboardDialogue(float time);
        void checkKeyboardEndDialogue(float time);
        void checkKeyboardFinal();
        sf::Font font;
        sf::Texture texture;
        sf::Texture chadText;
        sf::Texture girlText;
        sf::Texture titleText;
        sf::Sprite background;
        void drawObjects();
        int width;
        int height;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key up;
        sf::Keyboard::Key shoot;
        int waitingForKey;
        int currentLevel;
        //keeps track of which part of the dialogue the screen is in
        int dialogueStage;
        void drawDialogueBox();
        //time used for delay between dialogue screens
        float startTime;
        float currTime;
        //first used for dialogues and endLevel when scene only needs to be drawn once
        bool first;
        std::string response;
        std::string preference;
        int levelsWon;
        void readSaveFile();
        void writeSaveFile();
        bool checkDuplicateKeys(sf::Keyboard::Key);
    
    public: 
        HumanView(sf::RenderWindow& App, GameLogic& logic, sf::View& pView, Strings& s): View( logic ), display(App), view(pView),  strings(s) {};
        
        void init();

        void update(float time);
        void checkRebindingKeyPressed(sf::Keyboard::Key key);
        
        

};

#endif