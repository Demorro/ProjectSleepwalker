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

void Survivor::Update(float _deltaTime)
{
	//Check the units on a node, if not put it on one
	if(currentNode == NULL)
	{
		MoveImmediatelyToNode(navGrid->GetClosestNodeToPixelPos(getPosition().x, getPosition().y));
	}

	//Movement
	HandleMovement(_deltaTime);
}



void Survivor::Render(sf::RenderWindow &window)
{
	window.draw(*this);
}
