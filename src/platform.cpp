#include "platform.h"

/*
Class for a platform to be used in the levels
*/
Platform::Platform() {

}

void Platform::init(const float w, const float h, const float x, const float y, sf::IntRect rect, sf::Texture tiles) {
    scaleWidth = w;
    scaleHeight = h;
    xpos = x;
    ypos = y;

    setSprite(sf::Sprite(tiles));
    getSprite().setTextureRect(rect);
    getSprite().setScale(sf::Vector2f(scaleWidth, scaleHeight));
    getSprite().setPosition(xpos, ypos);
}
