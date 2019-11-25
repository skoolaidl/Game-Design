#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
#include "platform.h"
#include "tinyxml2.h"
#include "spike.h"
#include "enemy.h"
#include "girl.h"

class LevelCreator {
    private:

        sf::Sprite tiles;
        sf::Vector2i loadCounter = sf::Vector2i(0, 0);

        std::vector<Platform> platforms;
        std::vector<Spike> spikes;
        std::vector<Enemy> enemies;
        Girl girl;

    public:
        LevelCreator();
        void init();
        void LoadLevel(int level);
        std::vector<Platform> getPlatforms();
        std::vector<Spike> getSpikes();
        std::vector<Enemy> getEnemies();
        Girl getGirl();
        
};

#endif