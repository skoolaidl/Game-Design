#include "platform.h"

/*
Class for a platform to be used in the levels
*/
Platform::Platform() {

}

void Platform::init(const float w, const float h, const float x, const float y) {
    width = w;
    height = h;
    xpos = x;
    ypos = y;
    platform = sf::RectangleShape(sf::Vector2f(width, height));
    platform.setPosition(xpos, ypos);
}

sf::Drawable& Platform::getDrawable()
{
    return platform;
}