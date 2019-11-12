#include "projectile.h"

/*
Projectile class that is created and moved in a specified direction,
checks to see if it has run into anything 
*/

Projectile::Projectile(){ 
    isOffScreen = true;
}

void Projectile::init(int type, float x, float y, bool pDirection) {
    direction = pDirection;
    //set sprite according to type (fireball 0 or bullet 1)
    std::string text = "";
    switch (type) {
        case 0: text = (pDirection ? "../res/fireball_resized_1.png" : "../res/fireball_resized_0.png") ; break;
        case 1: text = (pDirection ? "../res/bullet_1.png" : "../res/bullet_0.png"); break;
    }
    if (!texture.loadFromFile(text))
    {
        // error...
    }
    setSprite(sf::Sprite(texture));
    getSprite().setPosition(x,y);
    startX = x;
    isOffScreen = false;
}



void Projectile::updateMovement(float timeS) {
    if (isOffScreen) {
        return;
    }
    if (direction) {
        getSprite().move(move_speed * timeS, 0);
    }
    else {
        getSprite().move(-(move_speed * timeS),0);
    }
}

bool Projectile::checkDistance() {
    if (direction) {
        if ( getSprite().getPosition().x > (startX + max_distance) ) {
            return false;
        }
    }
    else if ( getSprite().getPosition().x < (startX - max_distance)) {
        return false;
    }
    return true;
}

void Projectile::setOffScreen() {
    getSprite().setPosition(0, 650);
    isOffScreen = true;
}

