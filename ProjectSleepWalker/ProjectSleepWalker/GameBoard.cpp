#include "GameBoard.h"

GameBoard::GameBoard(int width, int height) 
	:	pathFindingGrid(width, height), map(width, height)
{
	map.Generate();
	RecalculatePathfindingGrid();

	map.SetTile(4,4,Tile::CLIFF);
	map.SetTile(4,5,Tile::CLIFF);
	map.SetTile(4,6,Tile::CLIFF);
	map.SetTile(6,4,Tile::CLIFF);
	map.SetTile(6,5,Tile::CLIFF);
	map.SetTile(6,6,Tile::CLIFF);
	map.SetTile(6,7,Tile::CLIFF);
	map.SetTile(6,8,Tile::CLIFF);
	map.SetTile(5,8,Tile::CLIFF);
	map.SetTile(4,8,Tile::CLIFF);
	map.SetTile(9,2,Tile::CLIFF);
	map.SetTile(11,6,Tile::CLIFF);
	map.SetTile(13,3,Tile::CLIFF);
}

GameBoard::~GameBoard()
{
}

void GameBoard::RecalculatePathfindingGrid()
{
	pathFindingGrid.Recalculate(map.GetTiles());
}

void GameBoard::Draw(sf::RenderWindow &window)
{
	map.Draw(window);
	
	if(MAP_DEBUG_MODE)
	{
		//The pathfinding grid only draws when you hold G, pretty cool for demoing
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
		{
			pathFindingGrid.Draw(window);
		}
	}
}
