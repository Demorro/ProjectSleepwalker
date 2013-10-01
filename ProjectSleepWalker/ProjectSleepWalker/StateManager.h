#pragma once

#include <iostream>
#include "State.h"
#include "GameState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "HelpState.h"

class StateManager
{
public:
	/** Default constructor. */
	StateManager(sf::RenderWindow& window);

	/** Default destructor. */
	~StateManager();

	/** 
		Switches the curState to the specified target state.
		@param stateID - The ID of the target state.
		@param window - Pointer to the application window.
	*/
	void SwitchState(State::StateID stateID, sf::RenderWindow& window);

	/** Main loop which updates the current state. */
	void Update(sf::Event events, bool eventFired);

	/** Draws the current state. */
	void Draw();

private:
	/** A pointer to the current state. */
	State* curState;
};
