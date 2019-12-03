#include "LevelCreator.h"


/* 
Level Creator class serves as an engine for reading in an XML file
and loading the proper components for that level to display to the player.
*/

LevelCreator::LevelCreator() {
}

void LevelCreator::init(){
    platforms.clear();
    spikes.clear();
    enemies.clear();
}

void LevelCreator::loadLevel(int level){
    //This line will change based on "level", for now just using Sample Level XML
    tinyxml2::XMLDocument map;
    tinyxml2::XMLError eResult; // = map.LoadFile("../res/practice_level.xml");
    switch(level)
    {
        case 0:
            eResult = map.LoadFile("../res/level1.xml");
            break;
        case 1:
            eResult = map.LoadFile("../res/level2.xml");
            break;
        case 2:
            eResult = map.LoadFile("../res/level3.xml");
            break;
        case 3:
            eResult = map.LoadFile("../res/level4.xml");
            break;
        case 4:
            eResult = map.LoadFile("../res/level5.xml");
            break;
    }
    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cout << "error loading file" << std::endl;
        return;
    }

    tinyxml2::XMLHandle docHandle(&map);

    tinyxml2::XMLElement *entry = docHandle.FirstChildElement("Actors").ToElement();


    if (entry) {
        for (tinyxml2::XMLNode *node = entry->FirstChildElement(); node; node = node->NextSibling()){

            tinyxml2::XMLElement *e = node->ToElement();

            if (std::string(e->Value()) == "Platform") {

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

            else if (std::string(e->Value()) == "Spike") {
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

            else if (std::string(e->Value()) == "Enemy") {
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
            else if (std::string(e->Value()) == "Girl") {
                std::string stringLocX = e->FirstChildElement("x")->GetText();
                std::string stringLocY = e->FirstChildElement("y")->GetText();

                float x = std::stof(stringLocX);
                float y = std::stof(stringLocY);
                girl.init(x, y);
            }
        }
    }
    std::cout << "loaded successfully" << std::endl;
}

std::vector<Platform>& LevelCreator::getPlatforms() {
    return platforms;
}

std::vector<Spike>& LevelCreator::getSpikes() {
    return spikes;
}

std::vector<Enemy>& LevelCreator::getEnemies() {
    return enemies;
}

Girl& LevelCreator::getGirl() {
    return girl;
}
