#ifndef AIVIEW_H
#define AIVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "view.h"
#include "GameLogic.h"

class AIView: public View {

	private:
		//display window
		sf::RenderWindow& display;
		sf::Font font;
		sf::Texture texture;
		void drawObjects();
		//variable that determines the current state of the game
		int gameState;
		int width;
		int height;

	public:
		AIView(GameLogic& logic);

        void init();

        void update(float time);                      


};

#endif
