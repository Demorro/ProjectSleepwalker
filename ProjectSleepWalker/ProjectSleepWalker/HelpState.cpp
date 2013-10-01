#include "HelpState.h"

HelpState::HelpState(sf::RenderWindow& window)
	:	State(State::HELP_STATE, window)
{
	background.setTexture(resourceManager.GetHelpBackgroundTex());
}

HelpState::~HelpState()
{
}

void HelpState::Update(sf::Event events, bool eventFired)
{

}

void HelpState::Draw()
{
	window.draw(background);
}

bool HelpState::Load()
{
	return true;
}
