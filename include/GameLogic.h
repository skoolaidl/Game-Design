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
        std::vector<unsigned int> scores = std::vector<unsigned int>(5, 0);
        //temporarily set arbitrary amounts for the goal scores of each level
        std::vector<unsigned int> goalScores = {400, 800, 1000, 1500, 1800};
        unsigned int pointsPerKill = 100;
        unsigned int scoreMultiplier = 1;
        int gameState = 0;
        int width;
        int height;
        float bulletSpeed;
        float gravity;
        int currentLevel = 0;
        float startTime = 0.f;
        float currTime = 0.f;
        int countDown = 0;
        bool playerFail = false;
        std::vector<bool> killPreferences = {false, false, false, false};

        Player player;
        Girl girl;

        LevelCreator loader;

        std::vector<std::reference_wrapper<Actor>> actorsVector;

        std::vector<Platform> platformVector;
        std::vector<Spike> spikeVector;
        std::vector<Enemy> enemyVector;
        std::vector<std::reference_wrapper<Platform>> platforms;
        std::vector<std::reference_wrapper<Spike>> spikes;
        std::vector<std::reference_wrapper<Projectile>> projectiles;
        std::vector<std::reference_wrapper<Enemy>> enemies;
        
        void softReset();
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
        void updateCountDown(float timeS);



	public:
	GameLogic();

        int getGameState();
        void setGameState(int newState);
        void init(int wWidth, int wHeight);
        void update(float timeS);
        void changeScore(int level, int increase);
        unsigned int getScore(int level);
        bool setScore(int level, unsigned int score);
        void resetScores();
        unsigned int getGoalScore(int level);
        void setLevel(int level);
        void addPreference(std::string pref, int type);

        Player& getPlayer();
        Actor& getGirl();
        std::vector<std::reference_wrapper<Actor>>& getActors();
        void playerMoveRight(float timeS);
        void playerMoveLeft(float timeS);
        void playerShoot();
        void enemyShoot(Enemy& enemy);
        void playerJump(float timeS);
        void playerFall(float time);
        void setCountDown(int levelTime);
        int getCountDown();
        bool getPlayerFail();

};

#endif
