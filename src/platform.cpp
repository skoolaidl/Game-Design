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
    if (!texture.loadFromFile("../res/cave_floor.jpg"))
    {
        // error...
    }
    texture.setRepeated(true);
    setSprite(sf::Sprite(texture));
    getSprite().setTextureRect({ 0, 0, (texture.getSize().x) * scaleWidth, (texture.getSize().y) * scaleHeight });
    //getSprite().setScale(sf::Vector2f(scaleWidth, scaleHeight));
    getSprite().setPosition(xpos, ypos);
}
