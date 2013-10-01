#include "HelpState.h"

HelpState::HelpState(sf::RenderWindow& window)
	:	State(State::HELP_STATE, window),
		controlsBtn(ResourceManager::GetTexture(ResourceManager::CONTROLS_BUTTON_TEXTURE), window, 202, 52),
		howToPlayBtn(ResourceManager::GetTexture(ResourceManager::HOW_TO_PLAY_BUTTON_TEXTURE), window, 202, 52),
		backBtn(ResourceManager::GetTexture(ResourceManager::BACK_BUTTON_TEXTURE), window, 202, 52)
{
	background.setTexture(ResourceManager::GetTexture(ResourceManager::HELP_BACKGROUND_TEXTURE));

	// Position buttons
	controlsBtn.setPosition(110.0f, 160.0f);
	howToPlayBtn.setPosition(110.0f, 230.0f);
	backBtn.setPosition(110.0f, 550.0f);
}

HelpState::~HelpState()
{
}

void HelpState::Update(sf::Event events, bool eventFired)
{
	HandleButtons();
}

void HelpState::Draw()
{
	window.draw(background);
	window.draw(controlsBtn);
	window.draw(howToPlayBtn);
	window.draw(backBtn);
}

bool HelpState::Load()
{
	return true;
}

void HelpState::HandleButtons()
{
	// Button handlers
	if(controlsBtn.Pressed(sf::Mouse::Left))
	{
		
	}

	if(howToPlayBtn.Pressed(sf::Mouse::Left))
	{

	}

	if(backBtn.Pressed(sf::Mouse::Left))
	{
		SwitchState(MENU_STATE);
	}

	// Update buttons
	controlsBtn.Update(sf::Mouse::Left);
	howToPlayBtn.Update(sf::Mouse::Left);
	backBtn.Update(sf::Mouse::Left);
}
