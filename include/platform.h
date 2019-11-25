#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "actor.h"

class Platform : public Actor {
    private:
        float scaleWidth;
        float scaleHeight;
        float xpos;
        float ypos;
        sf::Texture texture;

    public:
        Platform();
        void init(const float width, const float height, const float xpos, const float ypos);
        void setTexture();

};

#endif