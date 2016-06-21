#pragma once

#include "stdafx.h"
#include "Component.hpp"

class EnemyProjectileCom : public Component
{
public:
	enum Type {
		Regular
	};

	EnemyProjectileCom(Type type);

	Component::ComponentType getType() const;

	const Type type;
};