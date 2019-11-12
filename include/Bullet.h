#pragma once

#include <SFML/Graphics.hpp>

class Bullet {
    private:
        sf::RectangleShape bullet;
    
    public:
        Bullet(sf::Vector2f size){
            bullet.setSize(size);
            bullet.setFillColor(sf::Color::Red);
        }

        void init(sf::Vector2f size){
            bullet.setSize(size);
            bullet.setFillColor(sf::Color::Red);
        }

        int getRight(){
            return bullet.getPosition().x+bullet.getSize().x;
        }
    
        int getLeft(){
            return bullet.getPosition().x;
        }

        int getTop(){
            return bullet.getPosition().y;
        }

        int getDown(){
            return bullet.getPosition().y+bullet.getSize().y;
        }

        void updateMovement(int speed){
            bullet.move(speed,0);
        }

};
