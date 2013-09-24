#include "GameState.h"

GameState::GameState() : State(State::GAME_STATE)
{


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

void GameState::Draw(sf::RenderWindow &renderWindow)
{


}

void GameState::FindDeltaTime()
{
	//Using microseconds give us a high enough accuracy to get smooth movement.

	sf::Int64 oldTime;
	oldTime = newTime;
	newTime = deltaTimeClock.getElapsedTime().asMicroseconds();

	deltaTime = double(newTime - oldTime)/1000000;
	std::cout << deltaTime << std::endl;
}