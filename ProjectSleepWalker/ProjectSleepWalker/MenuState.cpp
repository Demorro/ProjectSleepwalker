#include "MenuState.h"
#include "Application.h"

MenuState::MenuState(sf::RenderWindow& window)
	:	State(State::MENU_STATE, window),
		playBtn(resourceManager.GetPlayButtonTex(), window, 247, 72),
		helpBtn(resourceManager.GetHelpButtonTex(), window, 247, 72),
		optionsBtn(resourceManager.GetOptionsButtonTex(), window, 247, 72),
		quitBtn(resourceManager.GetQuitButtonTex(), window, 247, 72)
{
	background.setTexture(resourceManager.GetMenuBackgroundTex());

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

void MenuState::Draw()
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
