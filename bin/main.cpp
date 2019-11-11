#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameLogic.h"
#include "HumanView.h"
#include "AIView.h"

int main(int argc, char** argv)
{
  int windowWidth = 800;
  int windowHeight = 600;
  sf::Clock clock;
  sf::RenderWindow App(sf::VideoMode(windowWidth,windowHeight,32), "Match Made in Hell", sf::Style::Titlebar | sf::Style::Close);
  sf::View view;
  
  // create GameLogic, player view, and AI view
  GameLogic logic;
  HumanView human(App, logic, view);
  AIView ai(logic);
  
  //init GameLogic and views
  logic.init(windowWidth, windowHeight);
  human.init();
  App.setVerticalSyncEnabled(true);
  
  bool focused = true;

  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed) {
          App.close();
      }
      else if (Event.type == sf::Event::LostFocus) {
          focused = false;
      }
      else if (Event.type == sf::Event::GainedFocus) {
          focused = true;
      }
    
      
    }
    if (focused) {
        float deltaS = clock.restart().asSeconds();
        deltaS = (deltaS < 1.f) ? 1.f : deltaS;
    
        logic.update(deltaS);
        human.update(deltaS);
        ai.update(deltaS);
    
    }
    
  }
  // Done.
  return 0;
}
