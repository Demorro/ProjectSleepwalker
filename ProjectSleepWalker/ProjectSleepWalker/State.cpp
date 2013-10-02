#include "State.h"

State::State(StateID ID)
{
	this->ID = targetID = ID;
}

State::~State()
{
}

State::StateID State::GetTarget()
{
	return targetID;
}

bool State::Switch()
{
	if(ID != targetID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void State::SwitchState(State::StateID state)
{
	targetID = state;
}
