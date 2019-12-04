#include "AudioController.h"

void AudioController::init() {
    fireball.loadFromFile("../res/fireball.wav");
    shotgun.loadFromFile("../res/gunshot.wav");
    jump.loadFromFile("../res/jump.wav");
    hit.loadFromFile("../res/hit.wav");
}

void AudioController::playSound(int soundNum) {
    switch (soundNum) {
        //fireball
    case 0: fireSound.setBuffer(fireball); fireSound.play(); break;
        //gunshot
    case 1: gunSound.setBuffer(shotgun); gunSound.play(); break;
        //jump
    case 2: jumpSound.setBuffer(jump); jumpSound.play(); break;
        //hit
    case 3: hitSound.setBuffer(hit); hitSound.play(); break;
    }
}