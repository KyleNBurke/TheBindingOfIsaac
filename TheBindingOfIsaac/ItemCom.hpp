#pragma once

#include "stdafx.h"
#include "Component.hpp"

class ItemCom : public Component
{
public:
	enum ItemType {
		ROF_Up,
		PlusTenBombs,
		RangeUp,
		ProjectileBombs,
		PlusOneHeart,
		PlusOneBomb
	};

	ItemCom(ItemType itemType, int price, sf::Vector2f entityPosition, sf::String description);
	ItemCom(ItemType itemType);

	Component::ComponentType getType() const;

	const ItemType itemType;
	const int price;
	sf::Text priceText;
	sf::String description;
};