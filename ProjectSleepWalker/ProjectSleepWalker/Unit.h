#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include "PathFindingNode.h"
#include "PathFindingGrid.h"
#include <iostream>
#include "SFML\System.hpp"
#include <queue>
#include "VectorMath.h"

class Unit : public sf::Sprite
{
public:
	Unit(PathFindingNode &nodeToStartOn, PathFindingGrid *navGridReference);

	~Unit();

	/** Abstract function intended to act as main update loop. */
	virtual void Update(float _deltaTime) = 0;

	/** Abstract function intended to render the unit and any components. */
	virtual void Render(sf::RenderWindow &window) = 0;

	// Getters
	std::string GetName();
	int GetCurHealth();
	int GetMaxHealth();
	sf::Vector2f GetAcceleration();
	sf::Vector2f GetVelocity();
	sf::Vector2f GetMaxVelocity();
	PathFindingNode* GetCurrentPathFindingNode();

	// Setters
	void SetCurHealth(int curHealth);
	void SetMaxHealth(int maxHealth);
	void SetName(std::string name);
	void SetAcceleration(sf::Vector2f acceleration);
	void SetVelocity(sf::Vector2f velocity);
	void SetMaxVelocity(sf::Vector2f maxVelocity);
	void SetAcceleration(float xAcc, float yAcc);
	void SetVelocity(float xVel, float yVel);
	void SetMaxVelocity(float maxXVel, float maxYVel);

	//The interface function that you call to actually order the unit to move
	void MoveTo(PathFindingNode* movementTargetNode);

protected:

	//A reference to the current pathfinding node this unit is on.
	PathFindingNode* currentNode;
	//A reference to a node that is the movement target, if there is one
	PathFindingNode* movementTargetNode;

	//The path that the unit is currently following. Calculated when you call MoveTo
	std::vector<PathFindingNode*> movementPath;

	//A reference to the entire nav-grid
	PathFindingGrid* navGrid;

	//This function is the passive function that handles the movement. Think of it as the units movement engine.
	void HandleMovement(float _deltaTime);

	//Calculate path from this units position to the target, A* This is the important one
	std::vector<PathFindingNode*> CalculatePathToTarget(PathFindingNode *movementTargetNode, PathFindingGrid &fullNavGrid);

	//Teleports the unit to a node;
	void MoveImmediatelyToNode(PathFindingNode* movementTargetNode);

private:
	// Not using constants for properties unless absolutely necessary
	std::string name;

	int curHealth;
	int maxHealth;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f maxVelocity;

	//This distance is the "elastic" distance that defines how far from a pathfinding node you can be before you are considered on it when moving. No need for getters/setters, just defined manually in the constructor.
	float nodeDistanceBeforeRecognition;
};
