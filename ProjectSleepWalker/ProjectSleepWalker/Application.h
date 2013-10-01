#pragma once

#include <SFML\Graphics.hpp>
#include "StateManager.h"

// Window properties
#define WINDOW_WIDTH		1280
#define WINDOW_HEIGHT		720
#define WINDOW_TITLE		"Project : GateKeeper"
#define WINDOW_V_SYNC		false
#define WINDOW_FRAMELIMIT	true
#define WINDOW_FRAMERATE	120

class Application
{
public:
	Application();

	~Application();

	/** Main update loop of the program. */
	void Run();

	// Setters
	static void SetRunning(bool running);

	// Getters
	static bool GetRunning();

private:
	StateManager* stateManager;

	/** Instance of the window used to catch events and display graphical content. */
	sf::RenderWindow window;

	/** Determines whether or not the application should continue to process. */
	static bool running;
};
