#include "PathFindingGrid.h"


PathFindingGrid::PathFindingGrid(int mapWidth, int mapHeight)
{
	pathFindingNodeDebugTexturePathable.loadFromFile(PATHFINDING_NODE_DEBUG_TEXTURE_PATHABLE);
	pathFindingNodeDebugTextureNotPathable.loadFromFile(PATHFINDING_NODE_DEBUG_TEXTURE_NOTPATHABLE);
	PopulatePathFindingGrid(mapWidth, mapHeight);

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

}


PathFindingGrid::~PathFindingGrid(void)
{
}

void PathFindingGrid::PopulatePathFindingGrid(int MAP_WIDTH, int MAP_HEIGHT)
{
	//Populate the pathfindingNodes
	for(int i = 0; i <= MAP_WIDTH * pathFindingNodeSubdivisionLevel; i++)
	{
		std::vector<PathFindingNode> pathfindingWidthVectorToAdd;
		pathFindingNodes.push_back(pathfindingWidthVectorToAdd);
		for(int j = 0; j <= MAP_HEIGHT * pathFindingNodeSubdivisionLevel; j++)
		{
			PathFindingNode nodeToAdd((i * MapTile::WIDTH)/pathFindingNodeSubdivisionLevel, ((j * MapTile::HEIGHT)/pathFindingNodeSubdivisionLevel),true);
			pathFindingNodes[i].push_back(nodeToAdd);
		}
	}

	//Populate the debug sprites for the pathfinding nodes. Would be more efficient in the above loop, but is seperate for better readibilty, and because this wont be active in actual gameplay, so it matters none.
	for(int i = 0; i < pathFindingNodes.size(); i++)
	{
		std::vector<sf::Sprite> pathfindingDebugSpritesWidthVectorToAdd;
		pathFindingNodeDebugSprites.push_back(pathfindingDebugSpritesWidthVectorToAdd);
		for(int j = 0; j < pathFindingNodes[i].size(); j++)
		{
			sf::Sprite spriteToAdd(pathFindingNodeDebugTexturePathable);
			spriteToAdd.setPosition(pathFindingNodes[i][j].GetPosition().x - spriteToAdd.getLocalBounds().width/2, pathFindingNodes[i][j].GetPosition().y - spriteToAdd.getLocalBounds().height/2);
			pathFindingNodeDebugSprites[i].push_back(spriteToAdd);
		}
	}
}

std::vector<std::vector<PathFindingNode>>& PathFindingGrid::GetPathFindingGrid()
{
	return pathFindingNodes;
}

void PathFindingGrid::DrawGridRepresentation(sf::RenderWindow &renderWindow)
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

PathFindingNode& PathFindingGrid::GetPathfindingNode(int pathFindingGridX, int pathFindingGridY)
{
	if((pathFindingGridX < pathFindingNodes.size()) && (pathFindingGridX >= 0))
	{
		if((pathFindingGridY < pathFindingNodes[pathFindingGridX].size()) && (pathFindingGridY >= 0))
		{
			return pathFindingNodes[pathFindingGridX][pathFindingGridY];
		}
	}

	std::cout << "Error, attempting to access a pathfinding node that isn't in the grid at X : " << pathFindingGridX << " Y : " << pathFindingGridY << std::endl << "Returning Node 0,0 " << std::endl;
	return pathFindingNodes[0][0];
}

void PathFindingGrid::RecalculatePathfindingGrid(std::vector<std::vector<MapTile>> &mapTiles)
{
	for(int i = 0; i < mapTiles.size(); i++)
	{
		for(int j = 0; j < mapTiles[i].size(); j++)
		{
			if(mapTiles[i][j].isPathable() == false)
			{
				//Set the entire tile to be non-pathable
				for(int k = 0; k < pathFindingNodeSubdivisionLevel + 1; k++)
				{
					for(int l = 0; l < pathFindingNodeSubdivisionLevel + 1; l++)
					{
						pathFindingNodes[i * (pathFindingNodeSubdivisionLevel) + k][j * (pathFindingNodeSubdivisionLevel) + l].SetPathable(false);
					}
				}
			}
		}
	}

	//Loop through the pathfinding notes and set the debug sprites to be correct
	for(int i = 0; i < pathFindingNodes.size(); i++)
	{
		for(int j = 0; j < pathFindingNodes[i].size(); j++)
		{
			//Set the debug sprites to be correct
			if(pathFindingNodes[i][j].IsPathable())
			{
				pathFindingNodeDebugSprites[i][j].setTexture(pathFindingNodeDebugTexturePathable);
			}
			else
			{
				pathFindingNodeDebugSprites[i][j].setTexture(pathFindingNodeDebugTextureNotPathable);
			}
		}
	}
}
