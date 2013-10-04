#pragma once

#include <SFML\Graphics.hpp>

class PathFindingNode
{
public:
	PathFindingNode(int xPos, int yPos, bool pathable, int navGridX, int navGridY);
	~PathFindingNode();

	// Setters
	void SetPathable(bool pathable);
	void SetPosition(sf::Vector2f position);

	// Getters
	bool IsPathable();
	sf::Vector2f GetPosition();
	sf::Vector2i GetNavGridPosition();

private:
	sf::Vector2f nodePosition;
	sf::Vector2i navGridPosition;
	bool pathable;
};
