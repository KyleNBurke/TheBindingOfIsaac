#pragma once

#include "stdafx.h"
#include "Floor.hpp"

class HUD
{
public:
	HUD();

	void draw(sf::RenderWindow& window);

	void constructFloor(const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& ar);

private:
	sf::Texture spriteSheet;
	sf::VertexArray floor;
	std::vector<sf::Sprite> hearts;
	sf::Sprite bomb;
	sf::Sprite coin;
};