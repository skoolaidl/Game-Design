#include "LevelCreator.h"
#include <iostream>
#include <string>

/* 
Level Creator class serves as an engine for reading in a specific level text file
and loading the proper tiles for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::LoadMap(int level){
    //This line will change based on "level", for now just using MapTest
    std::ifstream openfile("../res/MapTest.txt")

    if (openfile.is_open()){
        // std::string tileLocation;
        // openfile >> tileLocation;
        tiles.setTexture(mapTiles);
        while(!openfile.eof()){
            std::str tileLoc;
            openfile >> tileLoc;
            char x = tileLoc[0], y = tileLoc[2];
            if (!isDigit(x) || !isDigit(y)) map[loadCounter.x][loadCounter.y] = sf::vector2i(-1,-1);
            else map[loadCounter.x][loadCounter.y] = sf::vector2i(x - '0',y - '0');

            if (openfile.peek() == "\n"){
                loadCounter.x = 0;
                loadCounter.y++;
            }     
            else loadCounter.x++;
        }
        loadCounter.y++;
    }

}

void LevelCreator::SetMap() {

}

