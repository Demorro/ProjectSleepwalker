#include "Unit.h"

Unit::Unit()
{
	std::string name = "DefaultUnitName";
	maxHealth = curHealth = 0;
}

Unit::~Unit()
{
}

std::string Unit::GetName()
{
	return name;
}

int Unit::GetCurHealth()
{
	return curHealth;
}

int Unit::GetMaxHealth()
{
	return maxHealth;
}

sf::Vector2f Unit::GetAcceleration()
{
	return acceleration;
}

sf::Vector2f Unit::GetVelocity()
{
	return velocity;
}

sf::Vector2f Unit::GetMaxVelocity()
{
	return maxVelocity;
}

void Unit::SetCurHealth(int curHealth)
{
	this->curHealth = curHealth;
}

void Unit::SetMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

void Unit::SetName(std::string name)
{
	this->name = name;
}

void Unit::SetAcceleration(sf::Vector2f acceleration)
{
	this->acceleration = acceleration;
}

void Unit::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Unit::SetMaxVelocity(sf::Vector2f maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

void Unit::SetAcceleration(float xAcc, float yAcc)
{
	acceleration.x = xAcc;
	acceleration.y = yAcc;
}

void Unit::SetVelocity(float xVel, float yVel)
{
	velocity.x = xVel;
	velocity.y = yVel;
}

void Unit::SetMaxVelocity(float maxXVel, float maxYVel)
{
	maxVelocity.x = maxXVel;
	maxVelocity.y = maxYVel;
}
