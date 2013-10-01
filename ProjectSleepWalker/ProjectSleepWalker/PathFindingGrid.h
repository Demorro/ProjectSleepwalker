#pragma once
#include <iostream>
#include "Tile.h"
#include "ResourceManager.h"
#include "PathFindingNode.h"

class PathFindingGrid
{
public:
	PathFindingGrid(int mapWidth, int mapHeight);
	~PathFindingGrid(void);

	PathFindingNode& GetNode(int x, int y);
	std::vector<std::vector<PathFindingNode>> &GetGrid();

	// Draws a representation of the grid for debugging
	void Draw(sf::RenderWindow &window);

	// Recalculates all the collision on the nodes
	void Recalculate(std::vector<std::vector<Tile>> &mapTiles);

private:
	// The pathfinding node array, also known as the pathfinding grid
	std::vector<std::vector<PathFindingNode>> nodes;

	static const int NODE_SUBDIVISION_LEVEL = 4;
	std::vector<std::vector<sf::Sprite>> debugNodeSprites;

	// Populates the grid
	void Populate();

	// Stored from the constructor for calculation what nodes in what tale and what not ... WAHT!?
	int mapWidth;
	int mapHeight;
};
