#include "OptionsState.h"

OptionsState::OptionsState(sf::RenderWindow& window)
	:	State(State::OPTIONS_STATE, window),
		displayBtn(ResourceManager::GetTexture(ResourceManager::DISPLAY_BUTTON_TEXTURE), window, 202, 52),
		audioBtn(ResourceManager::GetTexture(ResourceManager::AUDIO_BUTTON_TEXTURE), window, 202, 52),
		backBtn(ResourceManager::GetTexture(ResourceManager::BACK_BUTTON_TEXTURE), window, 202, 52)
{
	background.setTexture(ResourceManager::GetTexture(ResourceManager::OPTIONS_BACKGROUND_TEXTURE));

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

void OptionsState::Draw()
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

