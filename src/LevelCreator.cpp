#include "LevelCreator.h"


/* 
Level Creator class serves as an engine for reading in a specific level text file
and loading the proper tiles for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::init(){

}

std::vector<std::vector<Actor>> LevelCreator::LoadMap(int level){
    //This line will change based on "level", for now just using MapTest
    // std::ifstream openfile("/Users/Seth/Desktop/Game-Design/res/MapTest.txt");

    //This line will change based on "level", for now just using Sample Level XML
    tinyxml2::XMLDocument map;
    // tinyxml2::XMLError eResult = map.LoadFile("/Users/Seth/Desktop/Game-Design/res/practice_level.xml");
    tinyxml2::XMLError eResult = map.LoadFile("../res/practice_level.xml");
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

                std::string stringScaleX = e->FirstChildElement("scaleX")->GetText();
                std::string stringScaleY = e->FirstChildElement("scaleY")->GetText();
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();

                float scaleX = std::stof(stringScaleX);
                float scaleY = std::stof(stringScaleY);
                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);
                

                Platform platform;
                platform.init(scaleX, scaleY, x, y);
                platforms.push_back(platform);

            }

            else if (std::strncmp(e->Value(), "Spike", 6) == 0) {
                std::string stringScaleX = e->FirstChildElement("scaleX")->GetText();
                std::string stringScaleY = e->FirstChildElement("scaleY")->GetText();
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();

                float scaleX = std::stof(stringScaleX);
                float scaleY = std::stof(stringScaleY);
                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);

            }

            else if (std::strncmp(e->Value(), "Enemy", 6) == 0) {
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();
                std::string stringColor = e->FirstChildElement("color")->GetText();

                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);
                float color = std::stof(stringColor);

            }
        }
        actorsVector.push_back(platforms);
    }
    return actorsVector;
}

