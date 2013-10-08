#pragma once
#include "unit.h"
#include "PathFindingNode.h"

class Survivor : public Unit
{
public:
	Survivor(PathFindingNode &nodeToStartOn, PathFindingGrid *navGird);
	~Survivor(void);

	void Update(float _deltaTime);
	void Render(sf::RenderWindow &window);
private:
	sf::Texture survivorTexture;

};

