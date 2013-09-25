#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include <iostream>

int main()
{
   // Window dimensions
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;

	bool eventFired = false;

    // Create the main window, needs to be passed into drea
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Project : GateKeeper");

	StateManager* stateManager = new StateManager();
		
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
			eventFired = true;
        }
		
		stateManager->Update(event,eventFired);
        window.clear();
		stateManager->Draw(window);
        window.display();
    }

    // Clean up routine
	stateManager = NULL;
	delete stateManager;

    return EXIT_SUCCESS;
}