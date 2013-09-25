#pragma once
#include "MapTile.h"
#include "Assets.h"
#include "PathFindingGrid.h"

//The gameboard starts at the top left at 0,0, extending leftwards and then downwards. So for example, to access the second tile across and the fourth one down, you would call GetTile(1,3), because the first row/column is 0,0;
class GameBoard
{
public:
	GameBoard(void);
	~GameBoard(void);

	//Toggle this to turn on/off the debug sprites. The crosses are visual representation of the pathfinding grid
	static const bool DEBUG_MAP = true;

	static const int MAP_WIDTH = 16;
	static const int MAP_HEIGHT = 9;

	void Draw(sf::RenderWindow &renderWindow);
	
	//This call changes the tile at the specified co-ordinates. Needs to be maintained as it also toggles the pathable variable
	void SetTile(int tileX, int tileY, MapTile::TileType tileToChangeTo);

	//Returns the tile at the specified grid reference
	MapTile& GetTile(int tileX, int tileY);

	//Recalculates the pathfinding
	void RecalculatePathfindingGrid();

private:
	//The main map array. Populated in, you guessed it, populateMap
	std::vector<std::vector<MapTile>> map;

	//The pathfinding grid
	PathFindingGrid pathFindingGrid;

	//These textures are stored here rather than in the tiles so you only need one copy of them.
	sf::Texture emptyTileTexture;
	sf::Texture grassTileTexture;
	sf::Texture cliffTileTexture;

	
	//Populates the map with tiles, run on initiation of the map. Also calculates the pathfinding nodes.
	void PopulateMap();
};

