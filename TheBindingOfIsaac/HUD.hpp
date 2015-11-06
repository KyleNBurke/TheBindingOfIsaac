#pragma once

#include "stdafx.h"

class HUD
{
public:
	HUD();

	void draw(sf::RenderWindow& window);

	void setMap(sf::VertexArray map);

private:
	sf::Texture spriteSheet;
	sf::VertexArray map;
	std::vector<sf::Sprite> hearts;
	const int initialHearts;
	sf::Sprite bomb;
	sf::Sprite coin;
};