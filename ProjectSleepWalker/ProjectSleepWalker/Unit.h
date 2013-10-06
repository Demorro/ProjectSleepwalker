#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include "PathFindingNode.h"
#include "PathFindingGrid.h"
#include <iostream>
#include <queue>

class Unit : public sf::Sprite
{
public:
	Unit(PathFindingNode &nodeToStartOn);

	~Unit();

	/** Abstract function intended to act as main update loop. */
	virtual void Update() = 0;

	/** Abstract function intended to render the unit and any components. */
	virtual void Render() = 0;

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

	//Calculate path from this units position to the target
	std::vector<PathFindingNode*> CalculatePathToTarget(PathFindingNode *targetNode, PathFindingGrid &fullNavGrid);

private:
	// Not using constants for properties unless absolutely necessary
	std::string name;

	int curHealth;
	int maxHealth;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f maxVelocity;

	//A reference to the current pathfinding node this unit is on.
	PathFindingNode* currentNode;

};
