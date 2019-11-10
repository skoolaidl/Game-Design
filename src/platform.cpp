#include "platform.h"

/*
Class for a platform to be used in the levels
*/
Platform::Platform() {

}

void Platform::init(const float w, const float h, const float x, const float y, sf::IntRect rect, sf::Sprite tiles) {
    scaleWidth = w;
    scaleHeight = h;
    xpos = x;
    ypos = y;
    // if (!texture.loadFromFile("../res/cave_floor.jpg"))
    // {
    //     // error...
    // }
    setSprite(sf::Sprite());
    getSprite().setTextureRect(rect);
    getSprite().setScale(sf::Vector2f(scaleWidth, scaleHeight));
    getSprite().setPosition(xpos, ypos);
}
