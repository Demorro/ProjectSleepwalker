#include "PathFindingNode.h"

PathFindingNode::PathFindingNode(int xPos, int yPos, bool pathable, int navGridX, int navGridY)
{
	nodePosition.x = xPos;
	nodePosition.y = yPos;
	this->pathable = pathable;
	navGridPosition.x = navGridX;
	navGridPosition.y = navGridY;
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

sf::Vector2f PathFindingNode::GetPosition()
{
	return nodePosition;
}