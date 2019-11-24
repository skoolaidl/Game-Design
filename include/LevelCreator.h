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
        struct Platform {
            std::int locX;
            std::int locY;
            std::int scaleX;
            std::int scaleY;
        };

        struct Spike {
            std::int locX;
            std::int locY;
            std::int color;
        };

        struct Enemy {
            std::int locX;
            std::int locY;
            std::int color;
        };

        

        sf::Sprite tiles;
        sf::Vector2i loadCounter = sf::Vector2i(0, 0);
        std::vector<Actor> actorsVector;
        std::string mapTiles =  ("/Users/Seth/Desktop/Game-Design/res/TileTest.png"); //change this once full tile set art completed
    public:
        LevelCreator();
        void init();
        void LoadMap(int level);
        std::vector<Actor> SetMap();
};

#endif