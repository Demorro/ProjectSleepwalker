#pragma once

#include <math.h>
#include "SFML\System.hpp"

/*
	Since sfml has no vector math facilities, thought it would be convenient to have a place to put some functions
*/


inline float VectorDistance(sf::Vector2i p1, sf::Vector2i p2)
{
	return sqrt((float)((p2.x - p1.x) * (float)(p2.x - p1.x)) + (float)((p2.y - p1.y) * (float)(p2.y - p1.y)));
}

inline float VectorDistance(sf::Vector2f p1, sf::Vector2f p2)
{
	return sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

inline float VectorDotProduct(sf::Vector2i p1, sf::Vector2i p2)
{
	return ((float)(p1.x * p2.x) + (float)(p1.y * p2.y));
}

inline float VectorDotProduct(sf::Vector2f p1, sf::Vector2f p2)
{
	return ((p1.x * p2.x) + (p1.y * p2.y));
}

inline float VectorMagnitude(sf::Vector2f vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

inline void NormaliseVector(sf::Vector2f &vector)
{
	vector /= VectorMagnitude(vector);
}
