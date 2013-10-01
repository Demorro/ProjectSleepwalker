#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Unit : public sf::Sprite
{
public:
	Unit();

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

private:
	// Not using constants for properties unless absolutely necessary
	std::string name;

	int curHealth;
	int maxHealth;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f maxVelocity;
};
