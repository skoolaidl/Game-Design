#ifndef AIVIEW_H
#define AIVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "view.h"
#include "GameLogic.h"

class AIView : public View {
	private:
		
	public:
		AIView(GameLogic& logic): View(logic) {};
		
		void init();
		
		void update(float time);                      
              
};

#endif