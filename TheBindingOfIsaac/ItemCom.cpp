#include "stdafx.h"
#include "ItemCom.hpp"

#include "Utilities.hpp"
#include "Room.hpp"

ItemCom::ItemCom(ItemType itemType, int price, sf::Vector2f entityPosition, sf::String description) : itemType(itemType), price(price), description(description)
{
	int scale = Utilities::getInstance().getScale();

	priceText.setFont(Utilities::getInstance().getFont());
	priceText.setString(std::to_string(price));
	priceText.setCharacterSize(scale * Room::tileSize);
	priceText.setPosition(entityPosition + sf::Vector2f(scale * -3.0f, scale * 2.0f));
}

ItemCom::ItemCom(ItemType itemType) : ItemCom(itemType, 0, sf::Vector2f(), "") {}

Component::ComponentType ItemCom::getType() const
{
	return Component::ComponentType::Item;
}
