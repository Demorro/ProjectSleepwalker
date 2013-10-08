#pragma once
#include "Map.h"
#include "PathFindingGrid.h"

// Toggles rendering of debug sprites. The crosses are visual representation of the pathfinding grid.
#define MAP_DEBUG_MODE true

/*
	The gamboard consists of the map, which represents the visual element of the board, and the pathfinding grid, 
	which handles the pathfinding and base-building elements of the board.
	It starts at the top left at (0,0) extending rightwards and then downwards. 
	For example, to access the second tile across and the fourth one down, you would call GetTile(1,3), because the first row/column is (0,0).
*/
class GameBoard
{
public:
	GameBoard(int width, int height);
	~GameBoard();
	
	void Draw(sf::RenderWindow &window);
	void RecalculatePathfindingGrid();
	PathFindingGrid *GetPathFindingGrid();

private:
	PathFindingGrid navGrid;
	Map map;
	
	void PopulateMap();
};

