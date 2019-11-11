#include "spike.h"

/*
Class for spikes to be used in the levels
*/
Spike::Spike() {

}

void Spike::init(const float w, const float h, const float x, const float y) {
    scaleWidth = w;
    scaleHeight = h;
    xpos = x;
    ypos = y;
    if (!texture.loadFromFile("../res/spike_trap.png"))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    getSprite().setScale(sf::Vector2f(scaleWidth, scaleHeight));
    getSprite().setPosition(xpos, ypos);
}
