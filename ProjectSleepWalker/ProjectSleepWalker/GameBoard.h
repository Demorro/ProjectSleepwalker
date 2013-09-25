#pragma once
#include "MapTile.h"
#include "Assets.h"


//The gameboard starts at the top left at 0,0, extending leftwards and then downwards. So for example, to access the second tile across and the fourth one down, you would call GetTile(1,3), because the first row/column is 0,0;
class GameBoard
{
public:
	GameBoard(void);
	~GameBoard(void);

	//Toggle this to turn on/off the debug sprites. The crosses are visual representation of the pathfinding grid
	static const bool DEBUG_MAP = true;

	static const int MAP_WIDTH = 32;
	static const int MAP_HEIGHT = 18;

	void Draw(sf::RenderWindow &renderWindow);
	
	void SetTileType(int tileX, int tileY, MapTile::TileType tileToChangeTo);

	//Returns the tile at the specified grid reference
	MapTile& GetTile(int tileX, int tileY);

	//Returns the pathfinding node at the specified pathfinding grid reference
	sf::Vector2f& GetPathfindingNode(int pathFindingGridX, int pathFindingGridY);
	//Returns the tile that the specified pathfinding node is on, if its on a border, the below or rightmost tile will be counted as the on one.
	MapTile& GetPathfindingNodeTile(int pathFindingGridX, int pathFindingGridY);

private:
	//The main map array. Populated in, you guessed it, populateMap
	std::vector<std::vector<MapTile>> map;

	//These textures are stored here rather than in the tiles so you only need one copy of them.
	sf::Texture emptyTileTexture;
	sf::Texture grassTileTexture;

	//The pathfinding node array, also known as the pathfinding grid
	std::vector<std::vector<sf::Vector2f>> pathFindingNodes;
	static const int pathFindingNodeSubdivisionLevel = 2;
	sf::Texture pathFindingNodeDebugTexture;
	std::vector<std::vector<sf::Sprite>> pathFindingNodeDebugSprites;

	//Populates the map with tiles, run on initiation of the map. Also calculates the pathfinding nodes.
	void PopulateMap();
};

