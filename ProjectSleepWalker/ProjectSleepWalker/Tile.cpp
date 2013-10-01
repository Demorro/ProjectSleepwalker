#include "Tile.h"

Tile::Tile(int xPos, int yPos, TileType tileType, sf::Texture &tileTex)
{
	setTexture(tileTex);
	setPosition(xPos, yPos);
	setScale(WIDTH/getLocalBounds().width, HEIGHT/getLocalBounds().height);

	isPathable = true;
	this->tileType = tileType;
}

Tile::~Tile()
{
}

void Tile::SetTile(TileType tileType, sf::Texture &tileImage)
{
	this->tileType = tileType;
	setTexture(tileImage);
}

void Tile::SetTile(TileType tileType, sf::Texture &tileImage, bool isPathable)
{
	this->tileType = tileType;
	setTexture(tileImage);
	this->isPathable = isPathable;
}

bool Tile::IsPathable()
{
	return isPathable;
}

void Tile::SetPathable(bool isPathable)
{
	this->isPathable = isPathable;
}
