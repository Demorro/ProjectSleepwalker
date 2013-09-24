#pragma once

#include <iostream>
#include "State.h"
#include "GameState.h"

class StateManager
{
public:
	/** Default constructor. */
	StateManager();

	/** Default destructor. */
	~StateManager();

	// States
	GameState* gameState;

	/** 
	 * Switches the curState to the specified target state.
	 * @param stateID The ID of the target state.
	 */
	void SwitchState(State::StateID stateID);

	/** Main loop which updates the current state. */
	void Update(sf::Event events, bool eventFired);

	/** Draws the current state. */
	void Draw(sf::RenderWindow &renderWindow);

private:
	/** A pointer to the current state. */
	State* curState;
};
