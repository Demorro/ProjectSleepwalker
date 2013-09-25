#pragma once
#include <iostream>
#include "MapTile.h"
#include "Assets.h"
#include "PathFindingNode.h"

class PathFindingGrid
{
public:
	PathFindingGrid(int mapWidth, int mapHeight);
	~PathFindingGrid(void);

	PathFindingNode& GetPathfindingNode(int pathFindingGridX, int pathFindingGridY);
	std::vector<std::vector<PathFindingNode>> &GetPathFindingGrid();

	//Draws a representation of the grid for debugging.
	void DrawGridRepresentation(sf::RenderWindow &renderWindow);

	//Recalculates all the collision on the nodes
	void RecalculatePathfindingGrid(std::vector<std::vector<MapTile>> &mapTiles);

private:
	//The pathfinding node array, also known as the pathfinding grid
	std::vector<std::vector<PathFindingNode>> pathFindingNodes;

	static const int pathFindingNodeSubdivisionLevel = 4;
	sf::Texture pathFindingNodeDebugTexturePathable;
	sf::Texture pathFindingNodeDebugTextureNotPathable;
	std::vector<std::vector<sf::Sprite>> pathFindingNodeDebugSprites;

	//Populates the pathfinding grid on start
	void PopulatePathFindingGrid(int mapWidth, int mapHeight);

	//Stored from the constructor for calculation what nodes in what tale and what not ... WAHT!?
	int mapWidth;
	int mapHeight;

};

