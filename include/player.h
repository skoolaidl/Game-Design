#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "shooter.h"
#include "platform.h"

class Player : public Shooter {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        float xpos;
        float ypos;
    
    public:
        Player();
        void init();
        sf::Drawable& getDrawable();
        void shoot();
        void move(float distanceX, float distanceY);
        void jump(float deltaS);
        bool collides(std::vector<Platform> objVector);
};

#endif