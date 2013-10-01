#pragma once
#include "State.h"
#include "ResourceManager.h"

class OptionsState : public State
{
public:
	OptionsState(sf::RenderWindow& window);

	~OptionsState();

	void Update(sf::Event events, bool eventFired);

	void Draw();

	bool Load();

private:
	sf::Sprite background;

};
