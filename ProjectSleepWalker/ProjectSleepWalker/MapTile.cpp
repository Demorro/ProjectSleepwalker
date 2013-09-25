#include "MapTile.h"


MapTile::MapTile(int xPos, int yPos, TileType tileType, sf::Texture &tileImage)
{
	//Sets the shared pointer to point to the texture passed in
	this->tileImage = std::make_shared<sf::Texture>(tileImage);

	if(this->tileImage != NULL)
	{
		setTexture(*this->tileImage);
		setPosition(xPos,yPos);
		setScale(WIDTH/getLocalBounds().width, HEIGHT/getLocalBounds().height);
	}
	else
	{
		std::cout << "Error in the tile image loading code. Check the constructor." << std::endl;
	}

	isPassable = true;
	this->tileType = tileType;
}


MapTile::~MapTile(void)
{
}

void MapTile::SetTileType(TileType newTileType, sf::Texture &newTileImage)
{
	tileType = newTileType;
	tileImage = std::make_shared<sf::Texture>(newTileImage);
}

bool MapTile::isPathable()
{
	return isPassable;
}

void MapTile::SetPathable(bool isPathable)
{
	isPassable = isPathable;
}
