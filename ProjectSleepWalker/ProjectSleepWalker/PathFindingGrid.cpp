#include "PathFindingGrid.h"

PathFindingGrid::PathFindingGrid(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	Populate();

	nodeDebugCircle.setFillColor(sf::Color::Transparent);
	nodeDebugCircle.setOutlineColor(sf::Color::Red);
	nodeDebugCircle.setOutlineThickness(2.0f);
	nodeDebugCircle.setRadius(8.0f);

	nodeDebugCircle.setPosition(0,0);
	nodeDebugCircle.setOrigin(nodeDebugCircle.getRadius(),nodeDebugCircle.getRadius());
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
			PathFindingNode node((i * Tile::WIDTH)/NODE_SUBDIVISION_LEVEL, ((j * Tile::HEIGHT)/NODE_SUBDIVISION_LEVEL), true, i, j);
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
			sf::Sprite openNode(TextureManager::GetTexture(Texture::OPEN_NODE));
			openNode.setPosition(nodes[i][j].GetPosition().x - openNode.getLocalBounds().width/2, nodes[i][j].GetPosition().y - openNode.getLocalBounds().height/2);
			debugNodeSprites[i].push_back(openNode);
		}
	}
}

PathFindingNode* PathFindingGrid::GetNode(int x, int y)
{
	if(NodeIsInGrid(x,y))
	{
		return &nodes[x][y];
	}

	std::cout << "Error, attempting to access a pathfinding node that isn't in the grid at X : " << x << " Y : " << y << std::endl << "Returning NULL Pointer." << std::endl;
	return NULL;
}

//Pass in the nav-grid x/y for the startnode, as well as the direction and how far you want to go to get a neighbor.
PathFindingNode* PathFindingGrid::GetNodeNeighbor(int startNodeXGridPos, int startNodeYGridPos, PathFindingGrid::Direction neighborDirection, int noOfJumps)
{
	if(!NodeIsInGrid(startNodeXGridPos,startNodeYGridPos))
	{
		std::cout << "Start node not in grid, returning NULL" << std::endl;
		return NULL;
	}
	//If we're here, then the start node at least is valid. For each direction, check if the neighbor is valid, if so return it
	if(neighborDirection == North)
	{
		if(NodeIsInGrid(startNodeXGridPos,startNodeYGridPos - noOfJumps))
		{
			return &nodes[startNodeXGridPos][startNodeYGridPos - noOfJumps];
		}
	}
	else if(neighborDirection == NorthEast)
	{
		if(NodeIsInGrid(startNodeXGridPos + noOfJumps,startNodeYGridPos - noOfJumps))
		{
			return &nodes[startNodeXGridPos + noOfJumps][startNodeYGridPos - noOfJumps];
		}
	}
	else if(neighborDirection == East)
	{
		if(NodeIsInGrid(startNodeXGridPos + noOfJumps,startNodeYGridPos))
		{
			return &nodes[startNodeXGridPos + noOfJumps][startNodeYGridPos];
		}
	}
	else if(neighborDirection == SouthEast)
	{
		if(NodeIsInGrid(startNodeXGridPos + noOfJumps,startNodeYGridPos + noOfJumps))
		{
			return &nodes[startNodeXGridPos + noOfJumps][startNodeYGridPos + noOfJumps];
		}
	}
	else if(neighborDirection == South)
	{
		if(NodeIsInGrid(startNodeXGridPos,startNodeYGridPos + noOfJumps))
		{
			return &nodes[startNodeXGridPos][startNodeYGridPos + noOfJumps];
		}
	}
	else if(neighborDirection == SouthWest)
	{
		if(NodeIsInGrid(startNodeXGridPos - noOfJumps,startNodeYGridPos + noOfJumps))
		{
			return &nodes[startNodeXGridPos - noOfJumps][startNodeYGridPos + noOfJumps];
		}
	}
	else if(neighborDirection == West)
	{
		if(NodeIsInGrid(startNodeXGridPos - noOfJumps,startNodeYGridPos))
		{
			return &nodes[startNodeXGridPos - noOfJumps][startNodeYGridPos];
		}
	}
	else if(neighborDirection == NorthWest)
	{
		if(NodeIsInGrid(startNodeXGridPos - noOfJumps,startNodeYGridPos - noOfJumps))
		{
			return &nodes[startNodeXGridPos - noOfJumps][startNodeYGridPos - noOfJumps];
		}
	}
	else
	{
		std::cout << "Invalid Node Direction" << std::endl;
	}

	//If we get here, there isnt a node at the specified position, return null
	std::cout << "Node neighbor not found, NULL" << std::endl;
	return NULL;
}

std::vector<std::vector<PathFindingNode>> &PathFindingGrid::GetGrid()
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

	nodeDebugCircle.setPosition(GetClosestNodeToPixelPos(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)->GetPosition());
	window.draw(nodeDebugCircle);
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
				debugNodeSprites[i][j].setTexture(TextureManager::GetTexture(Texture::OPEN_NODE));
			}
			else
			{
				debugNodeSprites[i][j].setTexture(TextureManager::GetTexture(Texture::CLOSED_NODE));
			}
		}
	}
}

bool PathFindingGrid::NodeIsInGrid(int startNodeXGridPos, int startNodeYGridPos)
{
	if((startNodeXGridPos < nodes.size()) && (startNodeXGridPos >= 0))
	{
		if((startNodeYGridPos < nodes[startNodeXGridPos].size()) && (startNodeYGridPos >= 0))
		{
			//this node is valid
			return true;
		}
	}
	return false;
}

bool PathFindingGrid::NodeIsInGrid(PathFindingNode node)
{
	if((node.GetNavGridPosition().x < nodes.size()) && (node.GetNavGridPosition().x >= 0))
	{
		if((node.GetNavGridPosition().y < nodes[node.GetNavGridPosition().x].size()) && (node.GetNavGridPosition().y >= 0))
		{
			//this node is valid
			return true;
		}
	}
	return false;
}

PathFindingNode* PathFindingGrid::GetClosestNodeToPixelPos(int x, int y)
{
	//Shift the x and y up and left half a grid interval to deal with the origin buisness
	x = x + ((Tile::WIDTH/ NODE_SUBDIVISION_LEVEL)/2.0f);
	y = y + ((Tile::HEIGHT/ NODE_SUBDIVISION_LEVEL)/2.0f);

	int xRef = x / (((float)Tile::WIDTH) / (NODE_SUBDIVISION_LEVEL));
	int yRef = y / (((float)Tile::HEIGHT) / (NODE_SUBDIVISION_LEVEL));

	
	//If the input is off the map, return the bounds
	//The int casts are important else when it gets a negative xRef it'll overflow and return the wrong bound
	if(xRef >= (int)nodes.size())
	{
		xRef = nodes.size() - 1;
	}
	if(xRef < 0)
	{
		xRef = 0;
	}
	if(yRef >= (int)nodes[xRef].size())
	{
		yRef = nodes[xRef].size() - 1; 
	}
	if(yRef < 0)
	{
		yRef = 0;
	}

	return &nodes[xRef][yRef];

}

PathFindingNode* PathFindingGrid::FindClosestPathableNode(PathFindingNode* node, int range)
{
	if(node != NULL)
	{
		if(node->IsPathable())
		{
			//if the node is already pathable, return itself
			return node;
		}

		PathFindingNode* currentNode;
		PathFindingNode* candidateNode;
		//The currentrange keeps track of how far out we are checking, dont go beyond the range specified.
		int currentRange = 1;
		currentNode = node;
		while((currentNode->IsPathable() == false) && (currentRange <= range))
		{
			//North
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,North,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//East
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,East,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//South
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,South,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//West
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,West,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//North-East
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,NorthEast,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//South-East
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,SouthEast,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//South-West
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,SouthWest,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}
			//North-West
			candidateNode = GetNodeNeighbor(currentNode->GetNavGridPosition().x,currentNode->GetNavGridPosition().y,NorthWest,currentRange);
			if(candidateNode != NULL)
			{
				if(candidateNode->IsPathable())
				{
					return candidateNode;
				}
			}

			currentRange++;
		}
		std::cout << "Couldnt find pathable node within range, returning null" << std::endl;
		return NULL;
	}
	std::cout << "Entered node to FindClosestPathableNode was invalid, returning null" << std::endl;
	return NULL;
}