#pragma once
#include "SFML\Graphics.hpp"
class PathFindingNode
{
public:
	PathFindingNode(int xPos, int yPos, bool pathable);
	~PathFindingNode(void);

	void SetPathable(bool pathable);
	bool IsPathable();
	sf::Vector2f GetPosition();
private:
	sf::Vector2f nodePosition;
	bool pathable;
};

