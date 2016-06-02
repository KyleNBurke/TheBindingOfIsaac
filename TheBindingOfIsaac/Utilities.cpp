#include "stdafx.h"
#include "Utilities.hpp"
#include "Room.hpp"

Utilities::Utilities() : scale(8) {}

Utilities& Utilities::getInstance()
{
	static Utilities instance;
	return instance;
}

void Utilities::initialize()
{
	font.loadFromFile("lucon.ttf");
}

float Utilities::round(float value) const
{
	return value > 0.0 ? std::floor(value + 0.5f) : std::ceil(value - 0.5f);
}

float Utilities::clamp(float value, float min, float max) const
{
	return value < min ? min : (value > max ? max : value);
}

float Utilities::getHorIntersectionDepth(sf::IntRect rectA, sf::IntRect rectB) const
{
	float halfA = rectA.width / 2.0f;
	float halfB = rectB.width / 2.0f;

	float centerA = rectA.left + halfA;
	float centerB = rectB.left + halfB;

	float distance = centerA - centerB;
	float minDistance = halfA + halfB;

	if (std::abs(distance) >= minDistance)
		return 0.0f;
	else
		return distance > 0 ? minDistance - distance : -minDistance - distance;
}

float Utilities::getVertIntersectionDepth(sf::IntRect rectA, sf::IntRect rectB) const
{
	float halfA = rectA.height / 2.0f;
	float halfB = rectB.height / 2.0f;

	float centerA = rectA.top + halfA;
	float centerB = rectB.top + halfB;

	float distance = centerA - centerB;
	float minDistance = halfA + halfB;

	if (std::abs(distance) >= minDistance)
		return 0.0f;
	else
		return distance > 0 ? minDistance - distance : -minDistance - distance;
}

int Utilities::getScale() const
{
	return scale;
}

sf::Font& Utilities::getFont()
{
	return font;
}