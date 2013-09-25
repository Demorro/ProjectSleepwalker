#pragma once
#include "SFML\Graphics.hpp"
#include <memory>
#include <iostream>
#include "Assets.h"

class MapTile : public sf::Sprite
{
public:

	enum TileType
	{
		EMPTY,
		GRASS,
		CLIFF,
	};

	MapTile(int xPos, int yPos, TileType tileType, sf::Texture &tileImage);
	~MapTile(void);

	void SetTile(TileType newTileType, sf::Texture &newTileImage);

	//Returns whether this tile can be pathed through
	bool isPathable();
	void SetPathable(bool isPathable);

	static const int WIDTH = 70;
	static const int HEIGHT = 70;
private:
	//The tile image is stored in the map, as opposed to making one for each individual tile.
	//By using a shared pointer, it ensures the pointed to image will not go out of scope and get deleted even if it should under other circumstances, but also means you dont need to copy the image for every tile.
	std::shared_ptr<sf::Texture> tileImage;

	//This boolean defines whether this tile is patheable or not. For example, a mountain will not be passable, but a flat plain will be
	bool isPassable;

	//The type of tile that this tile is. Set when this tile is created from the map class.
	TileType tileType;

};

