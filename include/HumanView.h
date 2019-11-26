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
        int dialogueStage;
        void drawDialogueBox();
        float startTime;
        float currTime;
        bool first;
        std::string response;
        std::string preferenceText;
        std::vector<std::string> preferencesVector;
        std::vector<int> enemyTypesVector;
        int levelsWon;
        void readSaveFile();
        void writeSaveFile();
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