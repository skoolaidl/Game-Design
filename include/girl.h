#pragma once
#include <SFML/Graphics.hpp>
#include "actor.h"

class Girl : public Actor {
private:
	float xpos;
	float ypos;
	sf::Texture texture;

public:
	Girl();
	void init(const float xpos, const float ypos);
	int getClassType();
};