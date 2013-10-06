#include "GameState.h"
#include "Application.h"

GameState::GameState() 
	: State(State::GAME_STATE), gameBoard(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT)
{
	gameBoard.RecalculatePathfindingGrid();

	testSurvivor = new Survivor(*gameBoard.GetPathFindingGrid()->GetNode(0,0));
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

	//PATHFINDING DEBUG CODE///////////////////////////////////////////
	//Just displays the path to where you click
	if((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (debugPathDone == false))
	{
		for(int i = 0; i < debugPath.size(); i++)
		{
			std::cout << "NODE " << i << " X : " << debugPath[i]->GetNavGridPosition().x << " Y : " << debugPath[i]->GetNavGridPosition().y << std::endl;
			gameBoard.GetPathFindingGrid()->debugNodeSprites[debugPath[i]->GetNavGridPosition().x][debugPath[i]->GetNavGridPosition().y].setColor(sf::Color::White);
			gameBoard.GetPathFindingGrid()->debugNodeSprites[debugPath[i]->GetNavGridPosition().x][debugPath[i]->GetNavGridPosition().y].setScale(1.0f,1.0f);
		}

		debugPath = testSurvivor->CalculatePathToTarget(gameBoard.GetPathFindingGrid()->GetClosestNodeToPixelPos(sf::Mouse::getPosition(Application::GetWindow()).x,sf::Mouse::getPosition(Application::GetWindow()).y),*gameBoard.GetPathFindingGrid());
		for(int j = 0; j < debugPath.size(); j++)
		{
			std::cout << "NODE " << j << " X : " << debugPath[j]->GetNavGridPosition().x << " Y : " << debugPath[j]->GetNavGridPosition().y << std::endl;
			gameBoard.GetPathFindingGrid()->debugNodeSprites[debugPath[j]->GetNavGridPosition().x][debugPath[j]->GetNavGridPosition().y].setColor(sf::Color::Black);
			gameBoard.GetPathFindingGrid()->debugNodeSprites[debugPath[j]->GetNavGridPosition().x][debugPath[j]->GetNavGridPosition().y].setScale(1.4f,1.4f);
		}
		debugPathDone = true;
	}
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		debugPathDone = false;
		debugPath.empty();
	}
	////////////////////////////////////////////////////////////////////
	
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
