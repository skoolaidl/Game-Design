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
#include "LevelCreator.h"
#include "girl.h"

class GameLogic {
    private:
        std::vector<int> scores = std::vector<int>(10, 0);
        int gameState = 0;
        int width;
        int height;
        float bulletSpeed;
        float gravity;

        Player player;
        Girl girl;
        Enemy enemy1;
        Enemy enemy2;
        Enemy enemy3;
        Enemy enemy4;
        Platform floor;
        Platform platformA;

        LevelCreator loader;

        std::vector<std::reference_wrapper<Actor>> actorsVector;
        std::vector<std::vector<Actor>> nestedActors;
        std::vector<Platform> platVector;
        std::vector<Spike> spikeVector;
        std::vector<Enemy> enemyVector;
        std::vector<std::reference_wrapper<Platform>> platforms;
        std::vector<std::reference_wrapper<Spike>> spikes;
        std::vector<std::reference_wrapper<Projectile>> projectiles;
        std::vector<std::reference_wrapper<Enemy>> enemies;
        
        void softReset();
        void reset();
        bool collides(Actor actor, std::vector<std::reference_wrapper<Actor>> objVector);
        void updatePlayerCollision(float timeS);
        void updatePlayerCollisionSpikesEnemy();
        void updatePlayerCollisionGirl();
        void updateProjectileCollisions();
        bool updatePlatformCollisions(Actor actor);
        void updateEnemyMovement(Enemy& enemy, float timeS);
        void enemyFall(Enemy& enemy, float timeS);
        void enemySetBounds(Enemy& enemy);
        void enemyTrack(Enemy& enemy, float timeS);

        void removeFromActorsVector(Actor& actor);



	public:
	GameLogic();

        int getGameState();
        void setGameState(int newState);
        
        void init(int wWidth, int wHeight);
        
        void update(float timeS);
                
        void increaseScore(int level, int increase);

        Player& getPlayer();
        Actor& getGirl();

        std::vector<std::reference_wrapper<Actor>>& getActors();

        void playerMoveRight(float timeS);

        void playerMoveLeft(float timeS);
        
        void playerShoot();
        void enemyShoot(Enemy& enemy);
        
        void playerJump(float timeS);
        
        void playerFall(float time);


};

#endif
