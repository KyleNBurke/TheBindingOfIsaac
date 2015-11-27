#include "stdafx.h"
#include "Component.hpp"

class WallCollisionCom : public Component
{
public:
	WallCollisionCom();

	Component::ComponentType getType() const;
};