#include "girl.h"

/*
Class for a girl to be used in the levels as the end of the level
*/
Girl::Girl() {

}

void Girl::init(const float x, const float y) {
	xpos = x;
	ypos = y;
	if (!texture.loadFromFile("../res/girl_resized.png"))
	{
		// error...
	}
	setSprite(sf::Sprite(texture));
	getSprite().setPosition(xpos, ypos);
}
