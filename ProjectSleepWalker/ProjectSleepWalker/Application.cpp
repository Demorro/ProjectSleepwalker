#include "Application.h"

bool Application::running = true;

Application::Application()
{
	// Initialise window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE);

	stateManager = new StateManager(window);

	// Load and set window icon
	//icon = assets.GetIconImage();
	//window.setIcon(icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr());

	if(WINDOW_FRAMELIMIT)
	{
		window.setFramerateLimit(WINDOW_FRAMERATE);
	}
	
	window.setVerticalSyncEnabled(WINDOW_V_SYNC);
}

Application::~Application()
{
	delete stateManager;
	stateManager = NULL;
}

void Application::Run()
{
	while(window.isOpen())
    {
		bool eventFired = false;

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
			eventFired = true;
        }

		stateManager->Update(event, eventFired);
        window.clear();
		stateManager->Draw();
        window.display();

		if(!GetRunning())
		{
			window.close();
		}
    }
}

void Application::SetRunning(bool running)
{
	Application::running = running;
}

bool Application::GetRunning()
{
	return running;
}
