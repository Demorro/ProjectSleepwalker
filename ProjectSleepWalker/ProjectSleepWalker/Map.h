#pragma once

#include "TextureManager.h"
#include "Tile.h"

class Map
{
public:
	Map(int width, int height);
	~Map();

	// Populates the map with tiles, run on initialisation of the map
	void Generate();

	void Draw(sf::RenderWindow& window);

	// This call changes the tile at the specified co-ordinates. Needs to be maintained as it also toggles the pathable variable
	void SetTile(int tileX, int tileY, Tile::TileType tileType);

	// Returns the tile at the specified grid reference
	Tile& GetTile(int tileX, int tileY);

	// Returns the vector of tiles
	std::vector<std::vector<Tile>> GetTiles();

private:
	int width;
	int height;

	std::vector<std::vector<Tile>> tiles;
};
