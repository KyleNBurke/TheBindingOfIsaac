#pragma once

#include "stdafx.h"
#include "Component.hpp"

class ItemCom : public Component
{
public:
	enum ItemType {
		//speedUp
		//doubleShot
		//etc.
	};

	ItemCom(ItemType itemType);

	Component::ComponentType getType() const;

	const ItemType itemType;
};