#include "GameState.h"
#include "Application.h"

GameState::GameState() 
	: State(State::GAME_STATE), gameBoard(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT)
{
	gameBoard.RecalculatePathfindingGrid();

	testSurvivor = new Survivor(*gameBoard.GetPathFindingGrid()->GetNode(30,15),gameBoard.GetPathFindingGrid());
	debugPathDone = false;
}

GameState::~GameState()
{
	delete testSurvivor;
}

bool GameState::Load()
{	
	return true;
}

void GameState::Update(sf::Event events, bool eventFired)
{
	FindDeltaTime();

	//Temp debug code
	if((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (debugPathDone == false))
	{
		testSurvivor->MoveTo(gameBoard.GetPathFindingGrid()->GetClosestNodeToPixelPos(sf::Mouse::getPosition(Application::GetWindow()).x,sf::Mouse::getPosition(Application::GetWindow()).y));
	}
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		debugPathDone = false;
		debugPath.empty();
	}
	testSurvivor->Update(deltaTime);
	////////////////////////////////////////////////////////////////////
	
	playerInterface.Update(Application::GetWindow());
}

void GameState::Draw(sf::RenderWindow& window)
{
	gameBoard.Draw(window);
	testSurvivor->Render(window);
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
