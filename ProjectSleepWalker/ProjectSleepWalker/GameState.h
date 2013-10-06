#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include <iostream>
#include "Tile.h"
#include "GameBoard.h"
#include "PlayerInterface.h"
#include "Survivor.h"

#define DEFAULT_MAP_WIDTH 16
#define DEFAULT_MAP_HEIGHT 9

class GameState : public State
{
public:
	/** Constructor initialiser. */
	GameState();

	/** Default destructor. */
	~GameState();

	/** 
		Loads GameState content.
		Returns true if successful, otherwise returns false.
	*/
	bool Load();
	
	/** Main loop. */
	void Update(sf::Event events, bool eventFired);

	/** Renders all of the applicable state content. */
	void Draw(sf::RenderWindow& window);

private:
	Survivor *testSurvivor;
	std::vector<PathFindingNode*> debugPath;
	bool debugPathDone;

	//The gameBoard
	GameBoard gameBoard;

	//The player interface
	PlayerInterface playerInterface;

	//Finds the delta time each frame. Multiply any time dependent action by deltaTime to get an action that moves at a speed independent of framerate
	void FindDeltaTime();
	//The deltaTime variable and two storage variables for finding it in FindDeltaTime()
	double deltaTime;
	sf::Int64 newTime;
	sf::Clock deltaTimeClock;
};
