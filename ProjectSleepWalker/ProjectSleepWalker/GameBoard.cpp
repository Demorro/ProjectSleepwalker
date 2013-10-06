#include "GameBoard.h"

GameBoard::GameBoard(int width, int height) 
	:	pathFindingGrid(width, height), map(width, height)
{
	map.Generate();
	RecalculatePathfindingGrid();

	map.SetTile(4,0,Tile::CLIFF);
	map.SetTile(4,1,Tile::CLIFF);
	map.SetTile(4,2,Tile::CLIFF);
	map.SetTile(4,3,Tile::CLIFF);
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
	map.SetTile(9,0,Tile::CLIFF);
	map.SetTile(9,1,Tile::CLIFF);
	map.SetTile(9,2,Tile::CLIFF);
	map.SetTile(10,5,Tile::CLIFF);
	map.SetTile(10,4,Tile::CLIFF);
	map.SetTile(10,3,Tile::CLIFF);
	map.SetTile(11,6,Tile::CLIFF);
	map.SetTile(13,3,Tile::CLIFF);
	map.SetTile(13,4,Tile::CLIFF);
	map.SetTile(13,5,Tile::CLIFF);
	map.SetTile(13,6,Tile::CLIFF);
	map.SetTile(13,7,Tile::CLIFF);
	map.SetTile(13,8,Tile::CLIFF);
	map.SetTile(14,3,Tile::CLIFF);
	map.SetTile(15,3,Tile::CLIFF);
}

GameBoard::~GameBoard()
{
}

PathFindingGrid* GameBoard::GetPathFindingGrid()
{
	return &pathFindingGrid;
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
