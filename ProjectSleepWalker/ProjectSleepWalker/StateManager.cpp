#include "StateManager.h"

StateManager::StateManager()
{
	curState = NULL;
	SwitchState(State::MENU_STATE);
}

StateManager::~StateManager()
{
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

	std::cout << "Switched to: ";

	switch(stateID)
	{
		case State::GAME_STATE:
			std::cout << "GAME." << std::endl;
			curState = new GameState();
		break;

		case State::OPTIONS_STATE:
			std::cout << "OPTIONS." << std::endl;
			curState = new OptionsState();
		break;

		case State::HELP_STATE:
			std::cout << "HELP." << std::endl;
			curState = new HelpState();
		break;

		case State::MENU_STATE:
			std::cout << "MENU." << std::endl;
			curState = new MenuState();
		break;
	}

	if(curState->Load() == false)
	{
		std::cout << "Failed to load state with ID : " << stateID << std::endl;
	}
}

void StateManager::Draw(sf::RenderWindow& window)
{
	if(curState != NULL)
	{
		curState->Draw(window);
	}
}
