#include "OptionsState.h"

OptionsState::OptionsState(sf::RenderWindow& window)
	:	State(State::OPTIONS_STATE, window)
{
	background.setTexture(resourceManager.GetOptionsBackgroundTex());
}

OptionsState::~OptionsState()
{
}

void OptionsState::Update(sf::Event events, bool eventFired)
{
	
}

void OptionsState::Draw()
{
	window.draw(background);
}

bool OptionsState::Load()
{
	return true;
}
