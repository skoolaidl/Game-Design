#pragma once
#include <SFML/Audio.hpp>

class AudioController {
    private:
        sf::SoundBuffer fireball;
        sf::SoundBuffer shotgun;
        sf::SoundBuffer jump;
        sf::SoundBuffer hit;
        sf::SoundBuffer enemyHit;
        sf::Sound jumpSound;
        sf::Sound gunSound;
        sf::Sound fireSound;
        sf::Sound hitSound;
        sf::Sound enemyHitSound;

    public:
        AudioController() {}
        void init();
        void playSound(int soundNum);
        

};