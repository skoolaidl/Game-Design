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
        void checkKeyboardStart();
        void checkKeyboardEndLevel();
        void drawEndLevel();
        void drawSettingsMenu();
        void drawLevelDialogue();
        void drawEndLevelDialogue();
        void checkKeyboardSettings();
        void checkKeyboardDialogue();
        sf::Keyboard::Key waitForKeyPress(sf::Keyboard::Key key);
        sf::Font font;
        sf::Texture texture;
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
    
    public: 
        HumanView(sf::RenderWindow& App, GameLogic& logic, sf::View& pView, Strings& s): View( logic ), display(App), view(pView),  strings(s) {};
        
        void init();

        void update(float time);
        
        

};

#endif