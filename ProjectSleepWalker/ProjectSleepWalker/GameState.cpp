#include "GameState.h"

GameState::GameState() : State(State::GAME_STATE)
{
}

GameState::~GameState()
{


}

bool GameState::Load()
{
	gameBoard.SetTile(4,4,MapTile::TileType::CLIFF);
	gameBoard.SetTile(4,5,MapTile::TileType::CLIFF);
	gameBoard.SetTile(4,6,MapTile::TileType::CLIFF);
	gameBoard.SetTile(6,4,MapTile::TileType::CLIFF);
	gameBoard.SetTile(6,5,MapTile::TileType::CLIFF);
	gameBoard.SetTile(6,6,MapTile::TileType::CLIFF);
	gameBoard.SetTile(6,7,MapTile::TileType::CLIFF);
	gameBoard.SetTile(6,8,MapTile::TileType::CLIFF);
	gameBoard.SetTile(5,8,MapTile::TileType::CLIFF);
	gameBoard.SetTile(4,8,MapTile::TileType::CLIFF);

	gameBoard.SetTile(9,2,MapTile::TileType::CLIFF);
	gameBoard.SetTile(11,6,MapTile::TileType::CLIFF);
	gameBoard.SetTile(13,3,MapTile::TileType::CLIFF);
	gameBoard.RecalculatePathfindingGrid();
	return true;
}

void GameState::Update(sf::Event events, bool eventFired)
{
	FindDeltaTime();
}

void GameState::Draw(sf::RenderWindow &renderWindow)
{
	gameBoard.Draw(renderWindow);
}

void GameState::FindDeltaTime()
{
	//Using microseconds give us a high enough accuracy to get smooth movement.

	sf::Int64 oldTime;
	oldTime = newTime;
	newTime = deltaTimeClock.getElapsedTime().asMicroseconds();

	deltaTime = double(newTime - oldTime)/1000000;
}