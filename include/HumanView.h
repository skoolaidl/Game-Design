#ifndef HUMANVIEW_H
#define HUMANVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "view.h"
#include "GameLogic.h"
#include "platform.h"

class HumanView : public View {
    
    private:
        //display window
        sf::RenderWindow& display;
        sf::View& view;
        void drawMenu();
        void checkKeyboard(float time);
        void checkKeyboardStart();
        void checkKeyboardEndLevel();
        void drawEndLevel();
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
    
    public: 
        HumanView(sf::RenderWindow& App, GameLogic& logic, sf::View& pView): View( logic ), display(App), view(pView) {};
        
        void init();

        void update(float time);
        
        

};

#endif