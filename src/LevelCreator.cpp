#include "LevelCreator.h"


/* 
Level Creator class serves as an engine for reading in a specific level text file
and loading the proper tiles for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::init(){

}

std::vector<Actor> LevelCreator::LoadMap(int level){
    //This line will change based on "level", for now just using MapTest
    // std::ifstream openfile("/Users/Seth/Desktop/Game-Design/res/MapTest.txt");

    //This line will change based on "level", for now just using Sample Level XML
    tinyxml2::XMLDocument map;
    tinyxml2::XMLError eResult = map.LoadFile("/Users/Seth/Desktop/Game-Design/res/practice_level.xml");
    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cout << "error loading file" << std::endl;
    };

    tinyxml2::XMLHandle docHandle(&map);

    tinyxml2::XMLElement *entry = docHandle.FirstChildElement("Actors").ToElement();


    if (entry) {
        for (tinyxml2::XMLNode *node = entry->FirstChildElement(); node; node = node->NextSibling()){

            tinyxml2::XMLElement *e = node->ToElement();

            std::cout << e->Value() << std::endl;

            if (std::strncmp(e->Value(), "Platform", 9) == 0) {
                std::string scaleX = e->FirstChildElement("scaleX")->GetText();
                std::string scaleY = e->FirstChildElement("scaleY")->GetText();
                std::string locX = e->FirstChildElement("x")->GetText();
                std::string locY = e->FirstChildElement("y")->GetText();
            }

            else if (std::strncmp(e->Value(), "Spike", 6) == 0) {
                std::string scaleX = e->FirstChildElement("scaleX")->GetText();
                std::string scaleY = e->FirstChildElement("scaleY")->GetText();
                std::string locX = e->FirstChildElement("x")->GetText();
                std::string locY = e->FirstChildElement("y")->GetText();
            }

            else if (std::strncmp(e->Value(), "Enemy", 6) == 0) {
                std::string scaleX = e->FirstChildElement("scaleX")->GetText();
                std::string scaleY = e->FirstChildElement("scaleY")->GetText();
                std::string color = e->FirstChildElement("color")->GetText();
            }
        }
    }
    return actorsVector
}

std::vector<Actor> LevelCreator::SetMap() {
    // for (int i = 0; i < loadCounter.x; i++){
    //     for (int j = 0; j < loadCounter.y; j++){
    //         std::cout << "map x is: " << map[i][j].x << std::endl;
    //         std::cout << "map j is: " << map[i][j].y << std::endl;
    //         std::cout << "i is: " << i << std::endl;
    //         std::cout << "j is: " << j << std::endl;
    //         if (map[i][j].x != -1 && map[i][j].y != -1){
    //             std::cout << "in here" << std::endl;
    //             Platform platform;
    //             sf::IntRect rect = sf::IntRect(map[i][j].x * 40, map[i][j].y * 40, 40, 40);
    //             platform.init(1, 1, 40 * i, 40 * j, rect, tileTexture);
    //             actorsVector.push_back(platform);
    //         } 
    //     }
    // }
    return actorsVector;
}

