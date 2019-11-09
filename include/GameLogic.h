#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "player.h"
#include "enemy.h"
#include "platform.h"
#include "spike.h"
#include "projectile.h"
#include "enemy.h"
#include "spike.h"

class GameLogic {
    private:
        std::vector<int> scores = std::vector<int>(10, 0);
        int gameState = 0;
        int width;
        int height;
        float bulletSpeed;
        float gravity;
        Player player;
        Enemy enemy;
        Platform floor;
        Platform platformA;
        Spike spike1;
        std::vector<std::reference_wrapper<Actor>> actorsVector;
        std::vector<std::reference_wrapper<Platform>> platforms;
        std::vector<std::reference_wrapper<Spike>> spikes;
        std::vector<std::reference_wrapper<Projectile>> projectiles;
        std::vector<std::reference_wrapper<Enemy>> enemies;
        
        void softReset();
        void reset();
        void updatePlayerCollision(float time);
        void updatePlayerCollisionSpikes();
        void updateProjectileCollisions();
        
		
	public:
		GameLogic();
                
        int getGameState();
        
        void init(int wWidth, int wHeight);
        
        void update(float time);
                
        void increaseScore(int level, int increase);

        Player& getPlayer();

        std::vector<std::reference_wrapper<Actor>> getActors();

        bool collides(Actor actor, std::vector<std::reference_wrapper<Actor>> objVector);

        void playerMoveRight(float time);

        void playerMoveLeft(float time);

        void playerJump(float time);
        
        void playerFall(float time);

        void enemyFall(float time);
        
};

#endif