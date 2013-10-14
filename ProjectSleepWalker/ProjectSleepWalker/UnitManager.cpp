#include "UnitManager.h"
#include "Application.h"

UnitManager::UnitManager(PathFindingGrid *navGrid, PlayerInterface *playerInterface)
{
	this->navGrid = navGrid;
	this->playerInterface = playerInterface;
}


UnitManager::~UnitManager(void)
{
}

void UnitManager::CreateSurvivor(int xNavGridPos, int yNavGridPos)
{
	std::unique_ptr<Survivor> newSurvivor(new Survivor(*navGrid->GetNode(xNavGridPos,yNavGridPos),navGrid));
	controllableUnits.push_back(std::move(newSurvivor));

}

void UnitManager::Update(float _deltaTime, sf::RenderWindow &window, sf::Event events)
{
	bool needToDeselect = false;
	//If we do a click and not a drag deselect everything
	if(playerInterface->SelectionBoxIsBeingDragged())
	{
		//Disregard if shift is being held
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) == false)
		{
			needToDeselect = true;
		}
	}

	//run the update logic on all the controllable units
	for(int i = 0; i < controllableUnits.size(); i++)
	{
		if(controllableUnits[i] != NULL)
		{
			if(needToDeselect)
			{
				controllableUnits[i]->Deselect();
			}
			controllableUnits[i]->Update(_deltaTime, window, events);
			controllableUnits[i]->HandleSelection(window, playerInterface, events);
		}
	}
}



void UnitManager::Render(sf::RenderWindow &window)
{
	//Loop through all the controllable units and render them
	for(int i = 0; i < controllableUnits.size(); i++)
	{
		if(controllableUnits[i] != NULL)
		{
			controllableUnits[i]->Render(window);
		}
	}
}
