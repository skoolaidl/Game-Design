#include "projectile.h"

/*
Projectile class that is created and moved in a specified direction,
checks to see if it has run into anything 
*/

Projectile::Projectile(){ 
    isAvailable = true;
}

void Projectile::init(int pType, float x, float y, bool pDirection) {
    direction = pDirection;
    type = pType;
    //set sprite according to type (fireball 0 or bullet 1)
    std::string text = "";
    switch (type) {
        case 0: 
            text = (pDirection ? "../res/fireball_resized_1.png" : "../res/fireball_resized_0.png");
            stepSize = 300.f;
            maxDistance = 350.f;
            break;
        case 1: 
            text = (pDirection ? "../res/bullet_1.png" : "../res/bullet_0.png");
            stepSize = 350.f;
            maxDistance = 200.f;
            break;
    }
    if (!texture.loadFromFile(text))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    getSprite().setPosition(x,y);
    startX = x;
    isAvailable = false;
}

void Projectile::setVelocity(float timeS)
{
    velocity = stepSize * timeS;
}

void Projectile::updateMovement() {
    if (isAvailable) {
        return;
    }
    if (direction) {
        getSprite().move(velocity, 0);
    }
    else {
        getSprite().move(-velocity,0);
    }
}

bool Projectile::checkDistance() {
    if (direction) {
        if ( getSprite().getPosition().x > (startX + maxDistance) ) {
            return false;
        }
    }
    else if ( getSprite().getPosition().x < (startX - maxDistance)) {
        return false;
    }
    return true;
}

void Projectile::setAvailable() {
    isAvailable = true;
}

bool Projectile::getIsAvailable() {
    return isAvailable;
}

int Projectile::getType() {
    return type;
}

