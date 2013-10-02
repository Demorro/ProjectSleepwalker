#include "Map.h"

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;
}

Map::~Map()
{
}

void Map::Generate()
{
	// Populate the map tiles
	for(int i = 0; i < width; i++)
	{
		std::vector<Tile> tileColumn;
		tiles.push_back(tileColumn);
		for(int j = 0; j < height; j++)
		{
			Tile tile(i * Tile::WIDTH, j * Tile::HEIGHT, Tile::GRASS, TextureManager::GetTexture(Texture::GRASS_TILE));
			tiles[i].push_back(tile);
		}
	}
}

void Map::SetTile(int tileX, int tileY, Tile::TileType tileType)
{
	// Check that the inputted tile numbers are in range.

	bool tileWithinBounds = true;

	if((tileX >= tiles.size()) || (tileX < 0))
	{
		tileWithinBounds = false;
	}
	else if((tileY >= tiles[tileX].size()) || (tileY < 0))
	{
		tileWithinBounds = false;
	}

	// Error
	if(!tileWithinBounds)
	{
		std::cout << "Error, attempting to access tile that isn't in the map at X : " << tileX << " Y : " << tileY << std::endl << "Not setting a tile type " << std::endl;
		return;
	}

	switch (tileType)
	{
		case Tile::EMPTY:
			tiles[tileX][tileY].SetTile(Tile::EMPTY, TextureManager::GetTexture(Texture::EMPTY_TILE), true);
			break;
		case Tile::GRASS:
			tiles[tileX][tileY].SetTile(Tile::GRASS, TextureManager::GetTexture(Texture::GRASS_TILE), true);
			break;
		case Tile::CLIFF:
			tiles[tileX][tileY].SetTile(Tile::CLIFF, TextureManager::GetTexture(Texture::CLIFF_TILE), false);
			break;
		default:
			std::cout << "Map::SetTile() error : tileType not recognised - empty texture assigned." << std::endl;
			tiles[tileX][tileY].SetTile(Tile::EMPTY, TextureManager::GetTexture(Texture::EMPTY_TILE), true);
			break;
	}
}

Tile& Map::GetTile(int tileX, int tileY)
{
	if((tileX < tiles.size()) && (tileX >= 0))
	{
		if((tileY < tiles[tileX].size()) && (tileY >= 0))
		{
			return tiles[tileX][tileY];
		}
	}

	std::cout << "Error, attempting to access tile that isn't in the map at X : " << tileX << " Y : " << tileY << std::endl << "Returning tiles[0][0]. " << std::endl;
	return tiles[0][0];
}

std::vector<std::vector<Tile>> Map::GetTiles()
{
	return tiles;
}

void Map::Draw(sf::RenderWindow& window)
{
	for(int i = 0; i < tiles.size(); i++)
	{
		for(int j = 0; j < tiles[i].size() ; j++)
		{
			window.draw(tiles[i][j]);
		}
	}
}
