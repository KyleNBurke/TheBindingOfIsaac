#include "stdafx.h"
#include "JimmyMoveCom.hpp"

JimmyMoveCom::JimmyMoveCom(sf::Vector2f centerPosition) : centerPosition(centerPosition), accelerationSpeed(2.0f) {}

Component::ComponentType JimmyMoveCom::getType() const
{
	return Component::ComponentType::JimmyMove;
}