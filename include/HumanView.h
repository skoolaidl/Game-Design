#ifndef HUMANVIEW_H
#define HUMANVIEW_H
#include <SFML/Graphics.hpp>
#include "view.h"
#include "GameLogic.h"

class HumanView : public View {
    
    private:
        //display window
        sf::RenderWindow& display;
        void checkKeyboard(float time);
        sf::Font font;
        sf::Texture texture;
        void drawObjects();
        //variable that determines the current state of the game
        int gameState;
        int width;
        int height;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key up;
        sf::Keyboard::Key shoot;
    
    public: 
        HumanView(sf::RenderWindow& App, GameLogic& logic): View( logic ), display(App) {};
        
        void init();
        void update(float time);
        
        

};

#endif