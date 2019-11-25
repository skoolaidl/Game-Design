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

class LevelCreator {
    private:

        sf::Sprite tiles;
        sf::Vector2i loadCounter = sf::Vector2i(0, 0);

        std::vector<std::vector<Actor>> actorsVector;
        std::vector<Actor> platforms;
        std::vector<Actor> spikes;
        std::vector<Actor> projectiles;
        std::vector<Actor> enemies;
        
        std::string mapTiles =  ("/Users/Seth/Desktop/Game-Design/res/TileTest.png"); //change this once full tile set art completed

    public:
        LevelCreator();
        void init();
        std::vector<std::vector<Actor>> LoadMap(int level);
        std::vector<Actor> SetMap();
};

#endif