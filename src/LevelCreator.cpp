#include "LevelCreator.h"
#include "platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

/* 
Level Creator class serves as an engine for reading in a specific level text file
and loading the proper tiles for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::init(){

}

void LevelCreator::LoadMap(int level){
    //This line will change based on "level", for now just using MapTest
    std::ifstream openfile("/Users/Seth/Desktop/Game-Design/res/MapTest.txt");

    if (openfile.is_open()){
        // std::string tileLocation;
        // openfile >> tileLocation;
        if (!tileTexture.loadFromFile(mapTiles))
        {
            std::cout << "error" << std::endl;
        }
        //tiles.setTexture(tileTexture);
        while(!openfile.eof()){
            std::string tileLoc;
            openfile >> tileLoc;
            char x = tileLoc[0], y = tileLoc[2];
            if (!isdigit(x) || !isdigit(y)) map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1,-1);
            else map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0',y - '0');

            if (openfile.peek() == '\n'){ 
                loadCounter.x = 0;
                loadCounter.y++;
            }     
            else loadCounter.x++;
        } 
        loadCounter.y++;
    }
}

std::vector<Actor> LevelCreator::SetMap() {
    for (int i = 0; i < loadCounter.x; i++){
        for (int j = 0; j < loadCounter.y; j++){
            std::cout << "map x is: " << map[i][j].x << std::endl;
            std::cout << "map j is: " << map[i][j].y << std::endl;
            std::cout << "i is: " << i << std::endl;
            std::cout << "j is: " << j << std::endl;
            if (map[i][j].x != -1 && map[i][j].y != -1){
                std::cout << "in here" << std::endl;
                Platform platform;
                sf::IntRect rect = sf::IntRect(map[i][j].x * 40, map[i][j].y * 40, 40, 40);
                platform.init(1, 1, 40 * i, 40 * j, rect, tileTexture);
                actorsVector.push_back(platform);
            } 
        }
    }
    return actorsVector;
}

