#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>
#include "GameLogic.h"
/*
Interface for views that holds shared capabilities between AIView and HumanView
*/
class View {
    
    protected:
    
    GameLogic& logic;
    
    public:
        View( GameLogic& logic ) : logic(logic) {};
        virtual void init() = 0;
        virtual void update(float time) = 0;
        
};

#endif