#include "Survivor.h"


Survivor::Survivor(PathFindingNode &nodeToStartOn, PathFindingGrid *navGird)
	:Unit(nodeToStartOn,navGird)
{
	setTexture(TextureManager::GetTexture(Texture::SURVIVOR_SPRITE));
	setPosition(0,0);
	//The 0.75f makes it appear though the sprite is standing on the node
	setOrigin(getLocalBounds().width/2,getLocalBounds().height * 0.75f);
	setPosition(nodeToStartOn.GetPosition());

	SetMaxVelocity(200.0f,200.0f);
}


Survivor::~Survivor(void)
{
}

void Survivor::Update(float _deltaTime, sf::RenderWindow &window, sf::Event events)
{
	//Check the units on a node, if not put it on one
	if(currentNode == NULL)
	{
		MoveImmediatelyToNode(navGrid->GetClosestNodeToPixelPos(getPosition().x, getPosition().y));
	}

	//Issue movement orders if needed, but only if selected
	if(IsSelected())
	{
		if (events.type == sf::Event::MouseButtonPressed)
		{
			if (events.mouseButton.button == sf::Mouse::Right)
			{
				MoveTo(navGrid->GetClosestNodeToPixelPos(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));
			}
		}
	}

	//Movement
	HandleMovement(_deltaTime);

}



void Survivor::Render(sf::RenderWindow &window)
{
	if(shouldDrawSelectionCircle)
	{
		window.draw(selectionCircle);
	}
	window.draw(*this);
}
