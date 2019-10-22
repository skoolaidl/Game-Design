#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "actor.h"

class Platform : public Actor {
    private:
        float width;
        float height;
        float xpos;
        float ypos;
        sf::RectangleShape platform;

    public:
        Platform();
        void init(const float width, const float height, const float xpos, const float ypos);
        sf::Drawable& getDrawable();
};

#endif