#include "GameBoard.h"


GameBoard::GameBoard(void)
{
	emptyTileTexture.loadFromFile(EMPTY_TILE_TEXTURE);
	grassTileTexture.loadFromFile(GRASS_TILE_TEXTURE);

	if(DEBUG_MAP)
	{
		pathFindingNodeDebugTexture.loadFromFile(PATHFINDING_NODE_DEBUG_TEXTURE);
	}

	PopulateMap();
}


GameBoard::~GameBoard(void)
{
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

	//Populate the pathfindingNodes
	for(int i = 0; i <= MAP_WIDTH * pathFindingNodeSubdivisionLevel; i++)
	{
		std::vector<sf::Vector2f> pathfindingWidthVectorToAdd;
		pathFindingNodes.push_back(pathfindingWidthVectorToAdd);
		for(int j = 0; j <= MAP_HEIGHT * pathFindingNodeSubdivisionLevel; j++)
		{
			sf::Vector2f nodeToAdd((i * MapTile::WIDTH)/pathFindingNodeSubdivisionLevel, (j * MapTile::HEIGHT)/pathFindingNodeSubdivisionLevel);
			pathFindingNodes[i].push_back(nodeToAdd);
		}
	}

	//Populate the debug sprites for the pathfinding nodes. Would be more efficient in the above loop, but is seperate for better readibilty, and because this wont be active in actual gameplay, so it matters none.
	if(DEBUG_MAP)
	{
		for(int i = 0; i < pathFindingNodes.size(); i++)
		{
			std::vector<sf::Sprite> pathfindingDebugSpritesWidthVectorToAdd;
			pathFindingNodeDebugSprites.push_back(pathfindingDebugSpritesWidthVectorToAdd);
			for(int j = 0; j < pathFindingNodes[i].size(); j++)
			{
				sf::Sprite spriteToAdd(pathFindingNodeDebugTexture);
				spriteToAdd.setPosition(pathFindingNodes[i][j].x - spriteToAdd.getLocalBounds().width/2, pathFindingNodes[i][j].y - spriteToAdd.getLocalBounds().height/2);
				pathFindingNodeDebugSprites[i].push_back(spriteToAdd);
			}
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
		//Render the debug markers for the pathfinding nodes
		for(int i = 0; i < pathFindingNodeDebugSprites.size(); i++)
		{
			for(int j = 0; j < pathFindingNodeDebugSprites[i].size(); j++)
			{
				renderWindow.draw(pathFindingNodeDebugSprites[i][j]);
			}
		}
	}
}

void GameBoard::SetTileType(int tileX, int tileY, MapTile::TileType tileToChangeTo)
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
		map[tileX][tileY].SetTileType(MapTile::TileType::EMPTY,emptyTileTexture);
		break;
	case MapTile::GRASS:
		map[tileX][tileY].SetTileType(MapTile::TileType::GRASS,grassTileTexture);
		break;
	default:
		std::cout << "SetTileType has failed, tileToChangeTo not recognised, just setting it to grass" << std::endl;
		map[tileX][tileY].SetTileType(MapTile::TileType::GRASS,grassTileTexture);
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

sf::Vector2f& GameBoard::GetPathfindingNode(int pathFindingGridX, int pathFindingGridY)
{
	if((pathFindingGridX < pathFindingNodes.size()) && (pathFindingGridX >= 0))
	{
		if((pathFindingGridY < pathFindingNodes[pathFindingGridX].size()) && (pathFindingGridY >= 0))
		{
			return pathFindingNodes[pathFindingGridX][pathFindingGridY];
		}
	}

	std::cout << "Error, attempting to access a pathfinding node that isn't in the grid at X : " << pathFindingGridX << " Y : " << pathFindingGridY << std::endl << "Returning Node 0,0 " << std::endl;
	return sf::Vector2f(0,0);
}

MapTile& GameBoard::GetPathfindingNodeTile(int pathFindingGridX, int pathFindingGridY)
{
	if((pathFindingGridX < pathFindingNodes.size()) && (pathFindingGridX >= 0))
	{
		if((pathFindingGridY < pathFindingNodes[pathFindingGridX].size())  && (pathFindingGridY >= 0))
		{
			std::cout << pathFindingGridY/pathFindingNodeSubdivisionLevel;
			return map[(pathFindingGridX/pathFindingNodeSubdivisionLevel)][(pathFindingGridY/pathFindingNodeSubdivisionLevel)];
		}
	}

	std::cout << "Error, attempting to access a Tile(via a pathfindingNode) that isn't in the grid at node position X : " << pathFindingGridX << " Y : " << pathFindingGridY << std::endl << "Returning map[0,0] " << std::endl;
	return map[0][0];
}