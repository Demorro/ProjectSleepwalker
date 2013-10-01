#include "GameState.h"

GameState::GameState(sf::RenderWindow& window) 
	: State(State::GAME_STATE, window), gameBoard(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT)
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
	FindDeltaTime();
}

void GameState::Draw()
{
	gameBoard.Draw(window);
}

void GameState::FindDeltaTime()
{
	// Using microseconds give us a high enough accuracy to get smooth movement.

	sf::Int64 oldTime;
	oldTime = newTime;
	newTime = deltaTimeClock.getElapsedTime().asMicroseconds();

	deltaTime = double(newTime - oldTime)/1000000;
}
