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
        void checkKeyboard(float timeS);
        void checkKeyboardStart(float timeS);
        void checkKeyboardEndLevel(float timeS);
        void drawEndLevel();
        void drawSettingsMenu();
        void drawLevelDialogue();
        void drawEndLevelDialogue();
        void drawFinalScore();
        void checkKeyboardSettings();
        void checkKeyboardDialogue(float timeS);
        void checkKeyboardEndDialogue(float timeS);
        void checkKeyboardFinal();
        sf::Font font;
        sf::Texture texture;
        sf::Texture chadTexture;
        sf::Texture girlTexture;
        sf::Texture titleTexture;
        sf::Texture speechBubbleTexture;
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
        void drawDialogueBox(int dir);
        //time used for delay between dialogue screens
        float startTime;
        float currTime;
        //first used for dialogues and endLevel when scene only needs to be drawn once
        bool first;
        std::string response;
        std::string preferenceText;
        std::vector<std::string> preferencesVector;
        std::vector<int> enemyTypesVector;
        int levelsWon;
        void readSaveFile();
        void writeSaveFile();
        bool checkDuplicateKeys(sf::Keyboard::Key);
        std::string removeRandomString(std::vector<std::string>& vec);
        int removeRandomInt(std::vector<int>& vec);
        void resetPreferencesVector();
        void resetEnemyTypesVector();
    
    public: 
        HumanView(sf::RenderWindow& App, GameLogic& logic, sf::View& pView, Strings& s): View( logic ), display(App), view(pView),  strings(s) {};
        
        void init();

        void update(float timeS);
        void checkRebindingKeyPressed(sf::Keyboard::Key key);
        
        

};

#endif