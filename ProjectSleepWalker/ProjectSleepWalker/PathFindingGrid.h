#pragma once
#include <iostream>
#include "Tile.h"
#include "TextureManager.h"
#include "PathFindingNode.h"

class PathFindingGrid
{
public:
	PathFindingGrid(int mapWidth, int mapHeight);
	~PathFindingGrid(void);

	//Used in the GetNeighbor function
	enum Direction
	{
		North,
		NorthEast,
		East,
		SouthEast,
		South,
		SouthWest,
		West,
		NorthWest
	};
	
	//Returns a pointer to a particular node, returns null if the node is invalid
	PathFindingNode* GetNode(int x, int y);
	//Returns a pointer to a node neighbor. Returns null if there isnt a node (UNTESTED)
	PathFindingNode* GetNodeNeighbor(int startNodeXGridPos, int startNodeYGridPos, PathFindingGrid::Direction neighborDirection, int noOfJumps = 1);

	//Gets the entire grid
	std::vector<std::vector<PathFindingNode>>* GetGrid();

	//A simple function that returns true if node is in grid, else it returns false, can pass in a grid reference or a node
	bool NodeIsInGrid(int startNodeXGridPos, int startNodeYGridPos);
	bool NodeIsInGrid(PathFindingNode node);

	//Gets the closest node to a pixel co-ord, used mainly in selecting a move position with the mouse
	PathFindingNode* GetClosestNodeToPixelPos(int x, int y);

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

	//Outlines the node under the mouse
	sf::CircleShape nodeDebugCircle;
};
