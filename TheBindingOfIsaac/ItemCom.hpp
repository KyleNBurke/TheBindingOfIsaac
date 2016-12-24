#pragma once

#include "stdafx.h"
#include "Component.hpp"

class ItemCom : public Component
{
public:
	enum ItemType {
		ROF_Up,
		PlusTenBombs
	};

	ItemCom(ItemType itemType, int price, sf::Vector2f entityPosition, sf::String description);

	Component::ComponentType getType() const;

	const ItemType itemType;
	const int price;
	sf::Text priceText;
	sf::String description;
};