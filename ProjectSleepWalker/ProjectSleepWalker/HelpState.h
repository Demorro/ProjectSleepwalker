#pragma once
#include "State.h"
#include "TextureManager.h"
#include "Button.h"

class HelpState : public State
{
public:
	HelpState();

	~HelpState();

	void Update(sf::Event events, bool eventFired);

	void Draw(sf::RenderWindow& window);

	bool Load();

private:
	sf::Sprite background;

	Button controlsBtn;
	Button howToPlayBtn;
	Button backBtn;

	void HandleButtons();
};
