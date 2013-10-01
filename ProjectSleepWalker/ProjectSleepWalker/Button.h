#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

/**
	BUTTON CLASS
	------------
	Represents a generic command button.
	Reacts to most mouse events.
*/
class Button
	:	public sf::Sprite
{
public:
	/**
		Default constructor.
		@param buttonTex - The texture of the button used for animation.
		@param BUTTON_WIDTH - The width of the button.
		@param BUTTON_HEIGHT - The height of the button.
	*/
	Button(sf::Texture& buttonTex, sf::RenderWindow& window, const unsigned int BUTTON_WIDTH, const unsigned int BUTTON_HEIGHT);

	~Button();

	/** Returns true if the mouse is over the button, otherwise returns false. */
	bool Over();

	/** Returns true if the mouse has been pressed and released over the button, otherwise returns false. */
	bool Up(sf::Mouse::Button mouseButton);

	/** Returns true if the mouse is down over the button, otherwise returns false. */
	bool Down(sf::Mouse::Button mouseButton);

	/** Returns true if the mouse has been pressed somewhere within the button region, otherwise returns flase. */
	bool Pressed(sf::Mouse::Button mouseButton);

	/** The button will not longer be updated if this is called, thus disabling user interaction. */
	void Disable();

	/** The button will be updated if this is called, thus enabling user interaction. */
	void Enable();

	/** Updates the state of the button depending on the user interaction. */
	virtual void Update(sf::Mouse::Button mouseButton);

protected:
	/** Unique IDs which determine the various states the button can be in. */
	enum ButtonState { BUTTON_DEFAULT, BUTTON_OVER, BUTTON_DOWN, BUTTON_UP, BUTTON_DISABLED };

	/** Will ignore user input when not active. */
	bool active;

	/** Holds the state of the button from the previous frame. */
	ButtonState prevState;

private:
	void SetState(ButtonState state);

	 const unsigned int BUTTON_WIDTH;
	 const unsigned int BUTTON_HEIGHT;

	 /** Pointer to the application window. */
	 sf::RenderWindow& window;
};
