#pragma once

#include <SFML\Graphics.hpp>

class PathFindingNode
{
public:
	PathFindingNode(int xPos, int yPos, bool pathable);
	~PathFindingNode();

	// Setters
	void SetPathable(bool pathable);

	// Getters
	bool IsPathable();
	sf::Vector2f GetPosition();

private:
	sf::Vector2f nodePosition;
	bool pathable;
};
