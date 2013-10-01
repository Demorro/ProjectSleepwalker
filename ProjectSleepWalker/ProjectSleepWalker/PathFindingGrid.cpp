#include "PathFindingGrid.h"

PathFindingGrid::PathFindingGrid(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	Populate();
}

PathFindingGrid::~PathFindingGrid()
{
}

void PathFindingGrid::Populate()
{
	// Populate the nodes
	for(int i = 0; i <= mapWidth * NODE_SUBDIVISION_LEVEL; i++)
	{
		std::vector<PathFindingNode> nodeColumn;
		nodes.push_back(nodeColumn);
		for(int j = 0; j <= mapHeight * NODE_SUBDIVISION_LEVEL; j++)
		{
			PathFindingNode node((i * Tile::WIDTH)/NODE_SUBDIVISION_LEVEL, ((j * Tile::HEIGHT)/NODE_SUBDIVISION_LEVEL), true);
			nodes[i].push_back(node);
		}
	}

	// Populate the debug sprites for the pathfinding nodes. Would be more efficient in the above loop, but is seperate for better readibilty, and because this wont be active in actual gameplay, so it matters none.
	for(int i = 0; i < nodes.size(); i++)
	{
		std::vector<sf::Sprite> debugNodeColumn;
		debugNodeSprites.push_back(debugNodeColumn);
		for(int j = 0; j < nodes[i].size(); j++)
		{
			sf::Sprite openNode(resourceManager.GetOpenNodeTex());
			openNode.setPosition(nodes[i][j].GetPosition().x - openNode.getLocalBounds().width/2, nodes[i][j].GetPosition().y - openNode.getLocalBounds().height/2);
			debugNodeSprites[i].push_back(openNode);
		}
	}
}

std::vector<std::vector<PathFindingNode>>& PathFindingGrid::GetGrid()
{
	return nodes;
}

void PathFindingGrid::Draw(sf::RenderWindow &window)
{
	// Render the debug markers for the pathfinding nodes
	for(int i = 0; i < debugNodeSprites.size(); i++)
	{
		for(int j = 0; j < debugNodeSprites[i].size(); j++)
		{
			window.draw(debugNodeSprites[i][j]);
		}
	}
}

PathFindingNode& PathFindingGrid::GetNode(int x, int y)
{
	if((x < nodes.size()) && (x >= 0))
	{
		if((y < nodes[x].size()) && (y >= 0))
		{
			return nodes[x][y];
		}
	}

	std::cout << "Error, attempting to access a pathfinding node that isn't in the grid at X : " << x << " Y : " << y << std::endl << "Returning node (0, 0)." << std::endl;
	return nodes[0][0];
}

void PathFindingGrid::Recalculate(std::vector<std::vector<Tile>> &mapTiles)
{
	for(int i = 0; i < mapTiles.size(); i++)
	{
		for(int j = 0; j < mapTiles[i].size(); j++)
		{
			if(mapTiles[i][j].IsPathable() == false)
			{
				//Set the entire tile to be non-pathable
				for(int k = 0; k < NODE_SUBDIVISION_LEVEL + 1; k++)
				{
					for(int l = 0; l < NODE_SUBDIVISION_LEVEL + 1; l++)
					{
						nodes[i * (NODE_SUBDIVISION_LEVEL) + k][j * (NODE_SUBDIVISION_LEVEL) + l].SetPathable(false);
					}
				}
			}
		}
	}

	// Loop through the pathfinding notes and set the debug sprites to be correct
	for(int i = 0; i < nodes.size(); i++)
	{
		for(int j = 0; j < nodes[i].size(); j++)
		{
			// Set the debug sprites to be correct
			if(nodes[i][j].IsPathable())
			{
				debugNodeSprites[i][j].setTexture(resourceManager.GetOpenNodeTex());
			}
			else
			{
				debugNodeSprites[i][j].setTexture(resourceManager.GetClosedNodeTex());
			}
		}
	}
}
