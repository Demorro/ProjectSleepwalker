#include "GameBoard.h"


GameBoard::GameBoard(void) : pathFindingGrid(MAP_WIDTH,MAP_HEIGHT)
{
	emptyTileTexture.loadFromFile(EMPTY_TILE_TEXTURE);
	grassTileTexture.loadFromFile(GRASS_TILE_TEXTURE);
	cliffTileTexture.loadFromFile(CLIFF_TILE_TEXTURE);


	PopulateMap();
	RecalculatePathfindingGrid();
}


GameBoard::~GameBoard(void)
{
}

void GameBoard::RecalculatePathfindingGrid()
{
	pathFindingGrid.RecalculatePathfindingGrid(map);
}

void GameBoard::PopulateMap()
{
	//Populate the map tiles
	for(int i = 0; i < MAP_WIDTH; i++)
	{
		std::vector<MapTile> widthVectorToAdd;
		map.push_back(widthVectorToAdd);
		for(int j = 0; j < MAP_HEIGHT; j++)
		{
			MapTile tileToAdd(i * MapTile::WIDTH, j * MapTile::HEIGHT, MapTile::TileType::GRASS, grassTileTexture);
			map[i].push_back(tileToAdd);
		}
	}

}

void GameBoard::Draw(sf::RenderWindow &renderWindow)
{
	for(int i = 0; i < map.size(); i++)
	{
		for(int j = 0; j < map[i].size() ; j++)
		{
			renderWindow.draw(map[i][j]);
		}
	}

	if(DEBUG_MAP)
	{
		pathFindingGrid.DrawGridRepresentation(renderWindow);
	}
}

void GameBoard::SetTile(int tileX, int tileY, MapTile::TileType tileToChangeTo)
{

	//Check that the inputted tile numbers are in range.
	if((tileX < map.size()) && (tileX >= 0))
	{
		if((tileY < map[tileX].size()) && (tileY >= 0))
		{
		}
		else
		{
			std::cout << "Error, attempting to access tile that isn't in the map at X : " << tileX << " Y : " << tileY << std::endl << "Not setting a tile type " << std::endl;
			return;
		}
	}
	else
	{
		std::cout << "Error, attempting to access tile that isn't in the map at X : " << tileX << " Y : " << tileY << std::endl << "Not setting a tile type " << std::endl;
		return;
	}

	switch (tileToChangeTo)
	{
	case MapTile::EMPTY:
		map[tileX][tileY].SetTile(MapTile::TileType::EMPTY,emptyTileTexture);
		map[tileX][tileY].SetPathable(true);
		break;
	case MapTile::GRASS:
		map[tileX][tileY].SetTile(MapTile::TileType::GRASS,grassTileTexture);
		map[tileX][tileY].SetPathable(true);
		break;
	case MapTile::CLIFF:
		map[tileX][tileY].SetTile(MapTile::TileType::CLIFF,cliffTileTexture);
		map[tileX][tileY].SetPathable(false);
		break;
	default:
		std::cout << "SetTile has failed, tileToChangeTo not recognised, just setting it to grass" << std::endl;
		map[tileX][tileY].SetTile(MapTile::TileType::GRASS,grassTileTexture);
		map[tileX][tileY].SetPathable(true);
		break;
	}

}

MapTile& GameBoard::GetTile(int tileX, int tileY)
{
	if((tileX < map.size()) && (tileX >= 0))
	{
		if((tileY < map[tileX].size()) && (tileY >= 0))
		{
			return map[tileX][tileY];
		}
	}

	std::cout << "Error, attempting to access tile that isn't in the map at X : " << tileX << " Y : " << tileY << std::endl << "Returning map[0][0]. " << std::endl;
	return map[0][0];
}
