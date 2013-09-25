#include "PathFindingNode.h"


PathFindingNode::PathFindingNode(int xPos, int yPos, bool pathable)
{
	nodePosition.x = xPos;
	nodePosition.y = yPos;
	this->pathable = pathable;
}


PathFindingNode::~PathFindingNode(void)
{
}

void PathFindingNode::SetPathable(bool pathable)
{
	this->pathable = pathable;
}

bool PathFindingNode::IsPathable()
{
	return pathable;
}

sf::Vector2f PathFindingNode::GetPosition()
{
	return nodePosition;
}