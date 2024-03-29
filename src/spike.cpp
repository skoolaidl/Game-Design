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
    if (!texture.loadFromFile("../res/Spikes_Fitted.png"))
    {
        // error...
    }
    texture.setRepeated(true);
    setSprite(sf::Sprite(texture));
    getSprite().setTextureRect({ 0, 0, int((texture.getSize().x) * scaleWidth), int((texture.getSize().y) * scaleHeight) });
    getSprite().setPosition(xpos, ypos);
}

void Spike::setTexture() {
    if (!texture.loadFromFile("../res/Spikes_Fitted.png"))
    {
        // error...
    }
    texture.setRepeated(true);
    setSprite(sf::Sprite(texture));
    getSprite().setTextureRect({ 0, 0, int((texture.getSize().x) * scaleWidth), int((texture.getSize().y) * scaleHeight) });
    getSprite().setPosition(xpos, ypos);
}

