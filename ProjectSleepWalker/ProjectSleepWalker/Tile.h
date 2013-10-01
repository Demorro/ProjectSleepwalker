#pragma once

#include "SFML\Graphics.hpp"
#include <memory>
#include <iostream>

class Tile : public sf::Sprite
{
public:

	enum TileType
	{
		EMPTY,
		GRASS,
		CLIFF,
	};

	Tile(int xPos, int yPos, TileType tileType, sf::Texture &tileImage);
	~Tile();

	void SetTile(TileType tileType, sf::Texture &tileTex);
	void SetTile(TileType tileType, sf::Texture &tileTex, bool isPathable);

	// Returns whether this tile can be pathed through
	bool IsPathable();
	void SetPathable(bool isPathable);

	static const int WIDTH = 70;
	static const int HEIGHT = 70;

private:
	//This boolean defines whether this tile is patheable or not. For example, a mountain will not be passable, but a flat plain will be
	bool isPathable;

	//The type of tile that this tile is. Set when this tile is created from the map class.
	TileType tileType;

};
