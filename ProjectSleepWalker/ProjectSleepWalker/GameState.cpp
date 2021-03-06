#include "GameState.h"
#include "Application.h"

GameState::GameState() 
	: State(State::GAME_STATE), gameBoard(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT)
{
	gameBoard.RecalculatePathfindingGrid();
}

GameState::~GameState()
{
}

bool GameState::Load()
{	
	return true;
}

void GameState::Update(sf::Event events, bool eventFired)
{
	playerInterface.Update(Application::GetWindow());
	FindDeltaTime();
}

void GameState::Draw(sf::RenderWindow& window)
{
	gameBoard.Draw(window);
	//Draw the interface on top
	playerInterface.Draw(window);
}

void GameState::FindDeltaTime()
{
	// Using microseconds give us a high enough accuracy to get smooth movement.

	sf::Int64 oldTime;
	oldTime = newTime;
	newTime = deltaTimeClock.getElapsedTime().asMicroseconds();

	deltaTime = double(newTime - oldTime)/1000000;
}
