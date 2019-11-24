#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor {
    private:
        sf::Sprite sprite;

    public :
        virtual sf::Sprite& getSprite() {return sprite;}
        virtual void setSprite(sf::Sprite s) {sprite = s;}
        bool operator==(const Actor &other);
        virtual int getClassType() {return -1;}
        
    
};

#endif