#pragma once
#include <SFML\Graphics.hpp>

class State
{
public:
	enum StateID
	{
		BEGIN_STATE,
		GAME_STATE,
		OPTIONS_STATE,
		HELP_STATE, 
		MENU_STATE
	};

	/** Constructor intended to set the inital ID. */
	State(StateID ID);

	/** Base destructor. */
	virtual ~State();

	/** Abstract method intended to act as the main loop of the state.*/
	virtual void Update(sf::Event events, bool eventFired) = 0;

	/** Abstract method intended to render all objects of the state. */
	virtual void Draw(sf::RenderWindow& window) = 0;

	/**
		* Abstract method intended to load state content.
		* For instance: positioning objects, loading images, setting parameters.
		* Returns true if the operation was successful, otherwise returns false.
		*/
	virtual bool Load() = 0;

	/** Returns the targetID variable. */
	StateID GetTarget();
		
	/** Returns true if targetID differs from ID, otherwise returns false. */
	bool Switch();

protected:
	/** The unique ID of the state. */
	StateID ID;

	/** Sets the state targetID value to the param. */
	void SwitchState(StateID state);

private:
	/** The unique ID of the desired state to switch to. */
	StateID targetID;
};
