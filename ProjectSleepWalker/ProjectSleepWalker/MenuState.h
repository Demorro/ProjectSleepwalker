#pragma once
#include "State.h"
#include "TextureManager.h"
#include "Button.h"

class MenuState : public State
{
public:
	MenuState();

	~MenuState();

	void Update(sf::Event events, bool eventFired);

	void Draw(sf::RenderWindow& window);

	bool Load();

private:
	sf::Sprite background;

	Button playBtn;
	Button quitBtn;
	Button helpBtn;
	Button optionsBtn;

	void HandleButtons();
};
