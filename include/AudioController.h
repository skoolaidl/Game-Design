#pragma once
#include <SFML/Audio.hpp>

class AudioController {
    private:
        sf::SoundBuffer fireball;
        sf::SoundBuffer shotgun;
        sf::SoundBuffer jump;
        sf::Sound jumpSound;
        sf::Sound gunSound;
        sf::Sound fireSound;

    public:
        AudioController() {}
        void init();
        void playSound(int soundNum);
        

};