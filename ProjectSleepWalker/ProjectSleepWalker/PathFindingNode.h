#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#define STRAIT_G_COST 10
#define DIAG_G_COST 14

class PathFindingNode
{
public:
	PathFindingNode(int xPos, int yPos, bool pathable, int navGridX, int navGridY);
	~PathFindingNode();

	// Setters
	void SetPathable(bool pathable);
	void SetPosition(sf::Vector2f position);

	void SetGCost(int gCost);
	void SetHeuristic(int heuristic);
	void SetParentNode(PathFindingNode* parentNode);
	void SetIsOnClosedList(bool onClosedList);
	void SetIsOnOpenList(bool onOpenList);

	// Getters
	bool IsPathable();
	sf::Vector2f GetPosition();
	sf::Vector2i GetNavGridPosition();
	int GetGCost();
	int GetHeuristic();
	//Calculates the F score from the current H and G score and then returns it
	int GetFScore();
	bool GetIsOnClosedList();
	bool GetIsOnOpenList();
	PathFindingNode* GetParentNode();

	//Clears all of the path specific values from the node for pathfinding.
	void ClearNodeValuesForPathFinding();
	//Works out G costs,
	void CalculateGScore(bool isDiagonalMove);
	//Calculates the Heuristic from a targetNode
	void CalculateHeuristic(PathFindingNode targetNode);
	//Calculates the FScore from the current heuristic and gCost
	void CalculateFScore();


private:
	//A pointer to the parent node of this node
	PathFindingNode *parentNode;

	//So the comparison can access G and H
	friend struct NodeCompareByFValue;
	friend struct NodePointerCompareByFValue;

	sf::Vector2f nodePosition;
	sf::Vector2i navGridPosition;

	//Pathfinding Variables
	int gCost;
	int heuristic;
	int fScore;
	bool pathable;
	bool isOnClosedList;
	bool isOnOpenList;

};

//For use in sorting the priority queue
struct NodeCompareByFValue
{
	//F Value is just G + H
	bool operator()(const PathFindingNode &node1, const PathFindingNode &node2) const
	{
		int node1value = node1.fScore;
		int node2value = node2.fScore;
		return node1value > node2value;
	}
};

//For use in sorting the priority queue
struct NodePointerCompareByFValue
{
	//F Value is just G + H
	bool operator()(const PathFindingNode *node1, const PathFindingNode *node2) const
	{
		int node1value = node1->fScore;
		int node2value = node2->fScore;
		return node1value > node2value;
	}
};
