#include "PathFindingNode.h"

PathFindingNode::PathFindingNode(int xPos, int yPos, bool pathable, int navGridX, int navGridY)
{
	nodePosition.x = xPos;
	nodePosition.y = yPos;
	navGridPosition.x = navGridX;
	navGridPosition.y = navGridY;

	this->pathable = pathable;
	ClearNodeValuesForPathFinding();
}

PathFindingNode::~PathFindingNode()
{
}

sf::Vector2i PathFindingNode::GetNavGridPosition()
{
	return navGridPosition;
}

void PathFindingNode::SetPathable(bool pathable)
{
	this->pathable = pathable;
}

bool PathFindingNode::IsPathable()
{
	return pathable;
}

void PathFindingNode::SetPosition(sf::Vector2f position)
{
	nodePosition = position;
}

void PathFindingNode::SetParentNode(PathFindingNode* parentNode)
{
	this->parentNode = parentNode;
}

void PathFindingNode::SetIsOnClosedList(bool onClosedList)
{
	isOnClosedList = onClosedList;
}

void PathFindingNode::SetIsOnOpenList(bool onOpenList)
{
	isOnOpenList = onOpenList;
}

sf::Vector2f PathFindingNode::GetPosition()
{
	return nodePosition;
}

void PathFindingNode::SetGCost(int gCost)
{
	this->gCost = gCost;
}

void PathFindingNode::SetHeuristic(int heuristic)
{
	this->heuristic = heuristic;
}

int PathFindingNode::GetGCost()
{
	return gCost;
}

int PathFindingNode::GetHeuristic()
{
	return heuristic;
}

int PathFindingNode::GetFScore()
{
	CalculateFScore();
	return fScore;
}

PathFindingNode* PathFindingNode::GetParentNode()
{
	return parentNode;
}

bool PathFindingNode::GetIsOnClosedList()
{
	return isOnClosedList;
}

bool PathFindingNode::GetIsOnOpenList()
{
	return isOnOpenList;
}

void PathFindingNode::ClearNodeValuesForPathFinding()
{
	SetHeuristic(0);
	SetGCost(0);
	fScore = 0;
	isOnClosedList = false;
	isOnOpenList = false;

	parentNode = NULL;
}

void PathFindingNode::CalculateGScore(bool isDiagonalMove)
{
	SetGCost(0);

	if(isDiagonalMove == false)
	{
		gCost = STRAIT_G_COST;
	}
	else if(isDiagonalMove == true)
	{
		gCost = DIAG_G_COST;
	}
	//Add the parents GCost to the current GCost
	if(parentNode != NULL)
	{
		gCost = gCost + parentNode->GetGCost();
	}
}

void PathFindingNode::CalculateHeuristic(PathFindingNode targetNode)
{
	//The diagonal shortcut method for calculating heuristic, is admissable in 8-way pathfinding and allows for influence mapping
	int xDistance = abs(navGridPosition.x - targetNode.GetNavGridPosition().x);
	int yDistance = abs(navGridPosition.y - targetNode.GetNavGridPosition().y);

	if (xDistance > yDistance)
	{
		heuristic = 14 * yDistance + 10 * (xDistance - yDistance);
	}
	else
	{
		heuristic = 14 * xDistance + 10 * (yDistance - xDistance);
	}
}

void PathFindingNode::CalculateFScore()
{
	fScore = gCost + heuristic;
}