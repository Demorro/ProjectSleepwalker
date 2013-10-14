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
#include "PlayerInterface.h"

class Unit : public sf::Sprite
{
public:
	Unit(PathFindingNode &nodeToStartOn, PathFindingGrid *navGridReference);

	~Unit();

	/** Abstract function intended to act as main update loop. */
	virtual void Update(float _deltaTime, sf::RenderWindow &window, sf::Event events) = 0;

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
	bool IsSelected();
	//Selected means the unit has been clicked on and it ready to be given commands too or whatever

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

	//Handles the unit selection, must be called every frame
	void HandleSelection(sf::RenderWindow &window, PlayerInterface *playerInterface, sf::Event events);

	//Call this when the unit gets selected, call deselect when it dosent
	void Select();
	void Deselect();

	//These functions toggle whether a unit is highlighter, ie if it has the selection crap around it
	void Highlight();
	void UnHightlight();

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
	std::vector<PathFindingNode*> CalculatePathToTarget(PathFindingNode *movementTargetNode, PathFindingGrid &fullNavGrid, bool shouldCallRecursively);

	//Teleports the unit to a node;
	void MoveImmediatelyToNode(PathFindingNode* movementTargetNode);

	//The circle that is displayed around the sprite when it is selected, remember you need to implement the rendering of this in the inherited class
	sf::CircleShape selectionCircle;
	bool shouldDrawSelectionCircle;

private:
	// Not using constants for properties unless absolutely necessary
	std::string name;

	int curHealth;
	int maxHealth;

	//If this unit is currently selected or not, toggled via Select()/Deselect()
	bool selected;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f maxVelocity;

	//This distance is the "elastic" distance that defines how far from a pathfinding node you can be before you are considered on it when moving. No need for getters/setters, just defined manually in the constructor.
	float nodeDistanceBeforeRecognition;
};
