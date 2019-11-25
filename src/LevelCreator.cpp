#include "LevelCreator.h"


/* 
Level Creator class serves as an engine for reading in a specific level text file
and loading the proper tiles for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::init(){

}

void LevelCreator::LoadLevel(int level){
    //This line will change based on "level", for now just using MapTest
    // std::ifstream openfile("../res/MapTest.txt");

    //This line will change based on "level", for now just using Sample Level XML
    tinyxml2::XMLDocument map;
    // tinyxml2::XMLError eResult = map.LoadFile("../res/practice_level.xml");
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

                Spike spike;
                spike.init(scaleX, scaleY, x, y);
                spikes.push_back(spike);

            }

            else if (std::strncmp(e->Value(), "Enemy", 6) == 0) {
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();
                std::string stringColor = e->FirstChildElement("color")->GetText();

                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);
                int color = std::stoi(stringColor);

                Enemy enemy;
                enemy.init(x, y, color);
                enemies.push_back(enemy);
            }
            else if (std::strncmp(e->Value(), "Girl", 4) == 0) {
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();

                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);
                girl.init(x, y);
            }
        }
    }
}

std::vector<Platform> LevelCreator::getPlatforms() {
    return platforms;
}

std::vector<Spike> LevelCreator::getSpikes() {
    return spikes;
}

std::vector<Enemy> LevelCreator::getEnemies() {
    return enemies;
}

Girl LevelCreator::getGirl() {
    return girl;
}
