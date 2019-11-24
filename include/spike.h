#ifndef SPIKE_H
#define SPIKE_H
#include <SFML/Graphics.hpp>
#include "actor.h"

class Spike : public Actor {
    private:
        float scaleWidth;
        float scaleHeight;
        float xpos;
        float ypos;
        sf::Texture texture;

    public:
        Spike();
        void init(const float width, const float height, const float xpos, const float ypos);
        int getClassType();
};

#endif