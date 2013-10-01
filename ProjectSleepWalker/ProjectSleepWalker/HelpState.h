#pragma once
#include "State.h"
#include "ResourceManager.h"

class HelpState : public State
{
public:
	HelpState(sf::RenderWindow& window);

	~HelpState();

	void Update(sf::Event events, bool eventFired);

	void Draw();

	bool Load();

private:
	sf::Sprite background;
};
