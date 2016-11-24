#include "stdafx.h"
#include "ItemCom.hpp"

ItemCom::ItemCom(ItemType itemType) : itemType(itemType) {}

Component::ComponentType ItemCom::getType() const
{
	return Component::ComponentType::Item;
}
