#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include "platform.h"

class LevelCreator {
    private:
        sf::Texture tileTexture;
        sf::Sprite tiles;
        sf::Vector2i map[100][100];
        sf::Vector2i loadCounter = sf::Vector2i(0, 0);
        std::vector<Actor> actorsVector;
        std::string mapTiles =  ("../res/TileTest.png"); //change this once full tile set art completed
    public:
        LevelCreator();
        void init(std::vector<Actor> actorsVec);
        void LoadMap(int level);
        void SetMap();
};

#endif