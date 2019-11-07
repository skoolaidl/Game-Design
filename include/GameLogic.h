#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "platform.h"
#include "LevelCreator.h"

class GameLogic {
    private:
        std::vector<int> scores = std::vector<int>(10, 0);
        int gameState = 0;
        int width;
        int height;
        float bulletSpeed;
        float gravity;
        Player player;
        Platform floor;
        Platform platformA;
        std::vector<Actor> actorsVector;
        
        void softReset();
        void reset();
        void updatePlayerCollision(std::vector<Actor> objVector, float time);
        
		
	public:
		GameLogic();
                
        int getGameState();
        
        void init(int wWidth, int wHeight);
        
        void update(float time);
                
        void increaseScore(int level, int increase);

        Player& getPlayer();

        std::vector<Actor>& getActors();

        bool collides(Actor actor, std::vector<Actor> objVector);

        void playerMoveRight(float time);

        void playerMoveLeft(float time);

        void playerJump(float time);
        
        void playerFall(float time);
        
};

#endif