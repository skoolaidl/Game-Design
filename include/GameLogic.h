#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"

class GameLogic {
    private:
        std::vector<int> scores = std::vector<int>(10, 0);
        int gameState = 0;
        int width;
        int height;
        float bulletSpeed;
        sf::Font font;
        Player player;
        
        void softReset();
        void reset();
        
		
	public:
		GameLogic();
                
        int getGameState();
        
        void init(int wWidth, int wHeight);
        
        void update(float time);
                
        void increaseScore(int level, int increase);

        Player& getPlayer();
        

        
};

#endif