#pragma once
#include "unit.h"
#include "PathFindingNode.h"
class Survivor : public Unit
{
public:
	Survivor(PathFindingNode &nodeToStartOn);
	~Survivor(void);

	void Update();
	void Render();
};

