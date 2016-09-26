#pragma once

#include "stdafx.h"
#include "Component.hpp"

class JimmyMoveCom : public Component
{
public:
	JimmyMoveCom(sf::Vector2f centerPosition);

	ComponentType getType() const;
	sf::Vector2f centerPosition;
	const float accelerationSpeed;
};