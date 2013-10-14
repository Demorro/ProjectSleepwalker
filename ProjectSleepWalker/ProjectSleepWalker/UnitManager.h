#pragma once
#include <vector>
#include "Survivor.h"
#include <memory>
#include "PlayerInterface.h"


//This class manages the units in the map, keeping a list of them and allowing the player to issue commands to the one he owns. Deals with selection and stuff.

class UnitManager
{
public:
	UnitManager(PathFindingGrid *navGrid, PlayerInterface *playerInterface);
	~UnitManager(void);

	//Adds another controller to the controllableUnits vector, effectively adding another unit to the game.
	void CreateSurvivor(int xNavGridPos, int yNavGridPos);

	//Updates the selection logic among other things
	void Update(float _deltaTime, sf::RenderWindow &window, sf::Event events);

	//Renders all the units that the manager owns
	void Render(sf::RenderWindow &window);

private:
	//This vector stores all the survivors as unique pointers.
	std::vector<std::unique_ptr<Survivor>> controllableUnits;

	//A reference to the nav grid, passed in in the constructor
	PathFindingGrid *navGrid;

	//A reference to the player interface, passed in in the constructor
	PlayerInterface *playerInterface;


};

