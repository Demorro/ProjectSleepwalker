#include "GameState.h"
#include "Application.h"

GameState::GameState() 
	: State(State::GAME_STATE), gameBoard(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT), unitManager(gameBoard.GetPathFindingGrid(),&playerInterface)
{
	gameBoard.RecalculatePathfindingGrid();
}

GameState::~GameState()
{

}

bool GameState::Load()
{
	unitManager.CreateSurvivor(1,14);
	unitManager.CreateSurvivor(2,14);
	unitManager.CreateSurvivor(3,14);
	unitManager.CreateSurvivor(4,14);
	unitManager.CreateSurvivor(5,14);
	unitManager.CreateSurvivor(1,15);
	unitManager.CreateSurvivor(2,15);
	unitManager.CreateSurvivor(3,15);
	unitManager.CreateSurvivor(4,15);
	unitManager.CreateSurvivor(5,15);



	return true;
}

void GameState::Update(sf::Event events, bool eventFired)
{
	FindDeltaTime();


		//testSurvivor->MoveTo(gameBoard.GetPathFindingGrid()->GetClosestNodeToPixelPos(sf::Mouse::getPosition(Application::GetWindow()).x,sf::Mouse::getPosition(Application::GetWindow()).y));

	unitManager.Update(deltaTime, Application::GetWindow(), events);
	playerInterface.Update(Application::GetWindow());
}

void GameState::Draw(sf::RenderWindow& window)
{
	gameBoard.Draw(window);
	unitManager.Render(window);
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
