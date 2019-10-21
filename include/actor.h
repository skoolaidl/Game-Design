#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>

class Actor {
    public :
        virtual sf::Drawable& getDrawable() = 0;
        
    
};

#endif