#include "Unit.h"

Unit::Unit(PathFindingNode &nodeToStartOn, PathFindingGrid *navGridReference)
{
	std::string name = "DefaultUnitName";
	maxHealth = curHealth = 0;

	currentNode = &nodeToStartOn;
	currentNode->SetPathable(false);

	if(navGridReference == NULL)
	{
		std::cout << "Nav Grid not passed into Unit correctly, fuck." << std::endl;
	}
	navGrid = navGridReference;

	nodeDistanceBeforeRecognition = 1.0f;
}

Unit::~Unit()
{
}

//These functions are only used in the calculatePathToTarget function, and thus arnt members. It dosent really make sense for them to be anyway
bool NodeIsValidForPathFinding(PathFindingNode *nodeToCheck)
{
	if(nodeToCheck != NULL)
	{
		if(nodeToCheck->IsPathable())
		{
			if(nodeToCheck->GetIsOnClosedList() == false)
			{
				return true;
			}
		}
	}
	return false;
}
void DoDirectionalPathFinding(PathFindingNode* adjacentNode, PathFindingNode* currentWorkingNode, PathFindingNode* targetNode, std::priority_queue<PathFindingNode*,std::vector<PathFindingNode*>,NodePointerCompareByFValue> &openList, bool diagonal)
{
	if(NodeIsValidForPathFinding(adjacentNode))
	{
		if(adjacentNode->GetIsOnOpenList() == false)
		{
			//Its not on the open list, so add it
			adjacentNode->SetParentNode(currentWorkingNode);
			adjacentNode->CalculateHeuristic(*targetNode);
			adjacentNode->CalculateGScore(diagonal);
			adjacentNode->CalculateFScore();
			adjacentNode->SetIsOnOpenList(true);
			openList.push(adjacentNode);
		}
		else
		{
			//Check to see if this way to this node is better that the one it already had, you know it already has one because its already on the open list
			if((currentWorkingNode->GetGCost() + STRAIT_G_COST) < adjacentNode->GetGCost())
			{
				//The G cost of going through the current node is less than the one it already has, so make this one the actual path
				adjacentNode->SetParentNode(currentWorkingNode);
				adjacentNode->CalculateGScore(diagonal);
				adjacentNode->CalculateFScore();

				//This is Fucking Important! The priority queue dosent like you changing the priority of items(in this case, the fScore) while they are already in the heap, will cause an invalid heap assetion error. This revalidates the heap after changing it.
				std::make_heap(const_cast<PathFindingNode**>(&openList.top()), const_cast<PathFindingNode**>(&openList.top()) + openList.size(), NodePointerCompareByFValue());
			}
		}
	}
}
//This is the A* imlementation. Probably the most important thing here
std::vector<PathFindingNode*> Unit::CalculatePathToTarget(PathFindingNode *movementTargetNode, PathFindingGrid &fullNavGrid)
{
	std::priority_queue<PathFindingNode*,std::vector<PathFindingNode*>,NodePointerCompareByFValue> openList;
	std::vector<PathFindingNode*> closedList;

	openList.empty();
	closedList.empty();

	//If the node isnt pathable, find the closest pathable node and use that. This is a good optimisation, as it prevents the inevitible recursion on nodes that are already tagged unpathable.
	PathFindingNode* closestNode = fullNavGrid.FindClosestPathableNode(movementTargetNode);
	if(closestNode != NULL)
	{
		movementTargetNode = closestNode;
	}
	
	//Switch the whole nav grid to nothing pathfinding wise
	for(int i = 0; i < fullNavGrid.GetGrid().size(); i++)
	{
		for(int j = 0; j < fullNavGrid.GetGrid()[i].size(); j++)
		{
			fullNavGrid.GetGrid()[i][j].ClearNodeValuesForPathFinding();
		}
	}

	//In case the target path isn't possible to get to, we keep track of what node in the path has the lowest h score, and if there is no path, we simply generate a path to that instead.
	//Should have the effect of trying to get as close as possible to the target. Need to calculate the startnode heuristic so it dosent just stick at 0
	currentNode->CalculateHeuristic(*movementTargetNode);
	PathFindingNode lowestHCost = *currentNode;

	
	//The current working node
	PathFindingNode* currentWorkingNode = NULL;
	
	//Add the starting node to the openlist
	if(currentNode == NULL)
	{
		std::cout << "Unit dosen't know what node it's on, can't pathfind." << std::endl;
		return std::vector<PathFindingNode*>();
	}
	currentNode->SetIsOnOpenList(true);
	openList.push(currentNode);
	
	//Keep track of this so if we dont find the end we can find the closest thing to it;
	bool foundEnd = false;

	//The pathfinding loop
	//while the openlist isn't empty
	while(openList.size() > 0)
	{
		//Get the lowest F score node off the top of the open list
		currentWorkingNode = openList.top();
		std::cout << "Current Working Node X : " << currentWorkingNode->GetNavGridPosition().x << " Y : " << currentWorkingNode->GetNavGridPosition().y << std::endl;
		openList.pop();
		currentWorkingNode->SetIsOnOpenList(false);

		//Set the new low heuristic value if neccesary
		if(currentWorkingNode->GetHeuristic() < lowestHCost.GetHeuristic())
		{
			lowestHCost = *currentWorkingNode;
		}

		//Add the current node to the closed list
		currentWorkingNode->SetIsOnClosedList(true);
		closedList.push_back(currentWorkingNode);

		//If the currentWorkingNode is the target node, then we have found the end
		if(currentWorkingNode->GetNavGridPosition() == movementTargetNode->GetNavGridPosition())
		{
			movementTargetNode->SetParentNode(currentWorkingNode->GetParentNode());
			foundEnd = true;
			break;
		}

		//For each of the 8 nodes surrounding
		PathFindingNode* adjacentNode = NULL;
		//North
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::North);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,false);
		//North-East
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::NorthEast);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,true);
		//East
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::East);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,false);
		//South-East
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::SouthEast);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,true);
		//South
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::South);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,false);
		//South-West
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::SouthWest);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,true);
		//West
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::West);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,false);
		//North-West
		adjacentNode = fullNavGrid.GetNodeNeighbor(currentWorkingNode->GetNavGridPosition().x, currentWorkingNode->GetNavGridPosition().y,PathFindingGrid::NorthWest);
		DoDirectionalPathFinding(adjacentNode,currentWorkingNode,movementTargetNode,openList,true);

	}

	if(foundEnd == true)
	{
		//Trace back
		std::vector<PathFindingNode*> traceBackNodes;
		PathFindingNode* workingTraceBackNode;
		workingTraceBackNode = currentWorkingNode;

		while(workingTraceBackNode->GetNavGridPosition() != currentNode->GetNavGridPosition())
		{
			traceBackNodes.push_back(workingTraceBackNode);
			workingTraceBackNode = workingTraceBackNode->GetParentNode();
		}

		return traceBackNodes;
	}
	else
	{
		//Recursion Bitch! Seriously though, if we dont find an end, find the path to the lowest h score we found along the path
		std::cout << "Couldn't find path, navigating to closest h score" << std::endl;
		return CalculatePathToTarget(&lowestHCost,fullNavGrid);
	}
}


//This is what you call to actually move to a point
void Unit::MoveTo(PathFindingNode* targetMoveNode)
{
	if(targetMoveNode != NULL)
	{
		if(currentNode != targetMoveNode)
		{
			movementPath = CalculatePathToTarget(targetMoveNode,*navGrid);
			if(movementPath.size() > 0)
			{
				movementTargetNode = movementPath.front();
			}
			else
			{
				std::cout << "There is no need to move to the target, unit is already there" << std::endl;
				movementTargetNode = NULL;
			}
		}
	}
}


//Runs the movement along the path
void Unit::HandleMovement(float _deltaTime)
{
	if((currentNode != NULL) && (movementTargetNode != NULL))
	{
		//If we are wanting to move somewhere.
		if((currentNode != movementTargetNode) && (movementPath.size() > 0))
		{
			PathFindingNode* nextNodeToGoTo = movementPath.back();
			sf::Vector2f moveVector = (nextNodeToGoTo->GetPosition() - getPosition());

			//If this isn't the last node on the path
			NormaliseVector(moveVector);

			moveVector.x *= GetMaxVelocity().x;
			moveVector.y *= GetMaxVelocity().y;

			moveVector *= _deltaTime;

			move(moveVector);

			
			if(VectorDistance(getPosition(),nextNodeToGoTo->GetPosition()) < VectorMagnitude(moveVector))
			{
				currentNode->SetPathable(true);
				currentNode = nextNodeToGoTo;
				currentNode->SetPathable(false);
				movementPath.pop_back();
				
				if(movementPath.size() == 0)
				{
					setPosition(currentNode->GetPosition());
				}
			}
			
		}
	}
}

void Unit::MoveImmediatelyToNode(PathFindingNode* movementTargetNode)
{
	if(movementTargetNode != NULL)
	{
		setPosition(movementTargetNode->GetPosition());
		currentNode = movementTargetNode;
	}
	else
	{
		std::cout << "Cannot move immediately to node, it dosen't seem to exist. Soz Bra!" << std::endl;
	}
}

std::string Unit::GetName()
{
	return name;
}

int Unit::GetCurHealth()
{
	return curHealth;
}

int Unit::GetMaxHealth()
{
	return maxHealth;
}

sf::Vector2f Unit::GetAcceleration()
{
	return acceleration;
}

sf::Vector2f Unit::GetVelocity()
{
	return velocity;
}

sf::Vector2f Unit::GetMaxVelocity()
{
	return maxVelocity;
}

PathFindingNode* Unit::GetCurrentPathFindingNode()
{
	if(currentNode != NULL)
	{
		return currentNode;
	}
	else
	{
		std::cout << "Current Node on this unit is null for some reason, this isn't so good" << std::endl;
		return NULL;
	}
}

void Unit::SetCurHealth(int curHealth)
{
	this->curHealth = curHealth;
}

void Unit::SetMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void Unit::SetName(std::string name)
{
	this->name = name;
}

void Unit::SetAcceleration(sf::Vector2f acceleration)
{
	this->acceleration = acceleration;
}

void Unit::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Unit::SetMaxVelocity(sf::Vector2f maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

void Unit::SetAcceleration(float xAcc, float yAcc)
{
	acceleration.x = xAcc;
	acceleration.y = yAcc;
}

void Unit::SetVelocity(float xVel, float yVel)
{
	velocity.x = xVel;
	velocity.y = yVel;
}

void Unit::SetMaxVelocity(float maxXVel, float maxYVel)
{
	maxVelocity.x = maxXVel;
	maxVelocity.y = maxYVel;
}

