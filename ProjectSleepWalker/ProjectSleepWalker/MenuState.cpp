#include "MenuState.h"
#include "Application.h"

MenuState::MenuState()
	:	State(State::MENU_STATE),
		playBtn(TextureManager::GetTexture(Texture::PLAY_BUTTON), 247, 72),
		helpBtn(TextureManager::GetTexture(Texture::HELP_BUTTON), 247, 72),
		optionsBtn(TextureManager::GetTexture(Texture::OPTIONS_BUTTON), 247, 72),
		quitBtn(TextureManager::GetTexture(Texture::QUIT_BUTTON), 247, 72)
{
	background.setTexture(TextureManager::GetTexture(Texture::MENU_BACKGROUND));

	// Position menu buttons
	playBtn.setPosition(55.0f, 610.0f);
	helpBtn.setPosition(355.0f, 610.0f);
	optionsBtn.setPosition(660.0f, 610.0f);
	quitBtn.setPosition(960.0f, 610.0f);
}

MenuState::~MenuState()
{
}

void MenuState::Update(sf::Event events, bool eventFired)
{
	HandleButtons();
}

void MenuState::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(playBtn);
	window.draw(helpBtn);
	window.draw(optionsBtn);
	window.draw(quitBtn);
}

bool MenuState::Load()
{
	return true;
}

void MenuState::HandleButtons()
{
	// Button handlers
	if(playBtn.Pressed(sf::Mouse::Left))
	{
		SwitchState(State::GAME_STATE);
	}

	if(optionsBtn.Pressed(sf::Mouse::Left))
	{
		SwitchState(State::OPTIONS_STATE);
	}

	if(helpBtn.Pressed(sf::Mouse::Left))
	{
		SwitchState(State::HELP_STATE);
	}

	if(quitBtn.Pressed(sf::Mouse::Left))
	{
		Application::SetRunning(false);
	}

	// Update buttons
	playBtn.Update(sf::Mouse::Left);
	helpBtn.Update(sf::Mouse::Left);
	optionsBtn.Update(sf::Mouse::Left);
	quitBtn.Update(sf::Mouse::Left);
}
