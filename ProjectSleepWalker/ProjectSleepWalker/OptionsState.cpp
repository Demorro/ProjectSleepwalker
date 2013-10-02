#include "OptionsState.h"

OptionsState::OptionsState()
	:	State(State::OPTIONS_STATE),
		displayBtn(TextureManager::GetTexture(Texture::DISPLAY_BUTTON), 202, 52),
		audioBtn(TextureManager::GetTexture(Texture::AUDIO_BUTTON), 202, 52),
		backBtn(TextureManager::GetTexture(Texture::BACK_BUTTON), 202, 52)
{
	background.setTexture(TextureManager::GetTexture(Texture::OPTIONS_BACKGROUND));

	// Position buttons
	
	
	displayBtn.setPosition(110.0f, 160.0f);
	audioBtn.setPosition(110.0f, 230.0f);
	backBtn.setPosition(110.0f, 550.0f);
}

OptionsState::~OptionsState()
{
}

void OptionsState::Update(sf::Event events, bool eventFired)
{
	HandleButtons();
}

void OptionsState::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(displayBtn);
	window.draw(audioBtn);
	window.draw(backBtn);
}

bool OptionsState::Load()
{
	return true;
}


void OptionsState::HandleButtons()
{
	// Button handlers
	if(displayBtn.Pressed(sf::Mouse::Left))
	{
		
	}

	if(audioBtn.Pressed(sf::Mouse::Left))
	{

	}

	if(backBtn.Pressed(sf::Mouse::Left))
	{
		SwitchState(MENU_STATE);
	}

	// Update buttons
	displayBtn.Update(sf::Mouse::Left);
	audioBtn.Update(sf::Mouse::Left);
	backBtn.Update(sf::Mouse::Left);
}

