#include "HelpState.h"

HelpState::HelpState()
	:	State(State::HELP_STATE),
		controlsBtn(TextureManager::GetTexture(Texture::CONTROLS_BUTTON), 202, 52),
		howToPlayBtn(TextureManager::GetTexture(Texture::HOW_TO_PLAY_BUTTON), 202, 52),
		backBtn(TextureManager::GetTexture(Texture::BACK_BUTTON), 202, 52)
{
	background.setTexture(TextureManager::GetTexture(Texture::HELP_BACKGROUND));

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

void HelpState::Draw(sf::RenderWindow& window)
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
