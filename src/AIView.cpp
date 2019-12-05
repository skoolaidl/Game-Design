#include "AIView.h"

void AIView::init() {
    
}

void AIView::update(float timeS) {
    //only active if game is running
    switch (logic.getGameState()) {
        case 0: break;
        //running
        case 1: break;
        //cycle through enemies and make them move, check if they should shoot    
        case 2: break;
        case 3: break;
        case 4: break;
    }
}
