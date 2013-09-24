#include "StateManager.h"

StateManager::StateManager()
{
	curState = NULL;
	
	SwitchState(State::GAME_STATE);
}

StateManager::~StateManager()
{
	// States
	delete gameState;
	gameState = NULL;


}

void StateManager::Update(sf::Event events, bool eventFired)
{
	if(curState != NULL)
	{
		// Switch the state if a signal has been given from the current state
		if(curState->Switch())
		{
			SwitchState(curState->GetTarget());
		}

		curState->Update(events, eventFired);
	}

}

void StateManager::SwitchState(State::StateID stateID)
{
	// Delete previous state, if set
	if(curState != NULL)
	{
		delete curState;
		curState = NULL;
	}

	std::cout << "State switched to: ";

	switch(stateID)
	{
		case State::GAME_STATE:
		std::cout << "GAME_STATE." << std::endl;
		curState = new GameState();
		break;
	}

	if(curState->Load() == false)
	{
		std::cout << "Failed to load state with ID : " << stateID << std::endl;
	}
}

void StateManager::Draw(sf::RenderWindow &renderWindow)
{
	if(curState != NULL)
	{
		curState->Draw(renderWindow);
	}
}
