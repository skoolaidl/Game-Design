#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

class Actor {
    private:
        sf::Sprite sprite;
        AnimatedSprite animatedSprite;
        bool animated;

    public :
        virtual sf::Sprite& getSprite() {return sprite;}
        virtual AnimatedSprite& getAnimatedSprite() {return animatedSprite;}
        virtual void setSprite(sf::Sprite s) {sprite = s;}
        virtual void setAnimatedSprite(AnimatedSprite aS) {animatedSprite = aS;}
        bool operator==(const Actor &other);
        void setAnimated(bool a) {animated = a;}
        bool isAnimated() {return animated;}
        
};

#endif