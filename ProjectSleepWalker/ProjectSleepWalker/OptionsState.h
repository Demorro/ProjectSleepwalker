#pragma once
#include "State.h"
#include "TextureManager.h"
#include "Button.h"

class OptionsState : public State
{
public:
	OptionsState();

	~OptionsState();

	void Update(sf::Event events, bool eventFired);

	void Draw(sf::RenderWindow& window);

	bool Load();

private:
	sf::Sprite background;

	Button displayBtn;
	Button audioBtn;
	Button backBtn;

	void HandleButtons();
};
