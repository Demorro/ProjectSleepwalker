#pragma once
#include "State.h"
#include "ResourceManager.h"
#include "Button.h"

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow& window);

	~MenuState();

	void Update(sf::Event events, bool eventFired);

	void Draw();

	bool Load();

private:
	sf::Sprite background;

	Button playBtn;
	Button quitBtn;
	Button helpBtn;
	Button optionsBtn;

	void HandleButtons();
};
