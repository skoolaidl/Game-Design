#include "platform.h"

/*
Class for a platform to be used in the levels
*/
Platform::Platform() {

}

void Platform::init(const float w, const float h, const float x, const float y) {
    scaleWidth = w;
    scaleHeight = h;
    xpos = x;
    ypos = y;
    // if (!texture.loadFromFile("/Users/Seth/Desktop/Game-Design/res/cave_floor.jpg"))
    if (!texture.loadFromFile("../res/cave_floor.jpg"))
    {
        // error...
    }
    texture.setRepeated(true);
    setSprite(sf::Sprite(texture));
    getSprite().setTextureRect({ 0, 0, int((texture.getSize().x) * scaleWidth), int((texture.getSize().y) * scaleHeight)});
    getSprite().setPosition(xpos, ypos);
}

