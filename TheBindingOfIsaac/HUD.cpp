#include "stdafx.h"
#include "HUD.hpp"
#include "Utilities.hpp"

HUD::HUD() : bomb(spriteSheet, sf::IntRect(7, 0, 4, 6)), coin(spriteSheet, sf::IntRect(11, 0, 6, 6)), initialHearts(15)
{
	spriteSheet.loadFromFile("Resources/HUD.png");

	float scale = (float)Utilities::getInstance().getScale();

	bomb.setScale(scale, scale);
	bomb.setPosition(66 * scale, 107 * scale);

	coin.setScale(scale, scale);
	coin.setPosition(65 * scale, 117 * scale);

	for(int i = 0; i < initialHearts; i++)
	{
		sf::Sprite heart = sf::Sprite(spriteSheet, sf::IntRect(0, 0, 7, 6));
		heart.setScale(scale, scale);
		heart.setPosition(88 * scale + 8 * (i % 6) * scale, 105 * scale);

		if(i > 11)
			heart.move(0, 14 * scale);
		else if(i > 5)
			heart.move(0, 7 * scale);

		hearts.push_back(heart);
	}
}

void HUD::setMap(sf::VertexArray map)
{
	this->map = map;
}

void HUD::draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(map, &spriteSheet);

	window.draw(bomb);
	window.draw(coin);

	for(std::vector<sf::Sprite>::iterator it = hearts.begin(); it != hearts.end(); ++it)
		window.draw(*it);
}