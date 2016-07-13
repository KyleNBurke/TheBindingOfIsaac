#include "stdafx.h"
#include "HUD.hpp"
#include "Utilities.hpp"

HUD::HUD() : bomb(spriteSheet, sf::IntRect(7, 0, 4, 6)), coin(spriteSheet, sf::IntRect(11, 0, 6, 6))
{
	spriteSheet.loadFromFile("Resources/HUD.png");
	floor.setPrimitiveType(sf::Quads);

	float scale = (float)Utilities::getInstance().getScale();

	bomb.setScale(scale, scale);
	bomb.setPosition(66 * scale, 107 * scale);

	coin.setScale(scale, scale);
	coin.setPosition(65 * scale, 117 * scale);

	for(int i = 0; i < 15; i++)
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

void HUD::constructFloor(const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& ar)
{
	sf::Vertex vertTL;
	sf::Vertex vertBL;
	sf::Vertex vertBR;
	sf::Vertex vertTR;

	float scale = (float)Utilities::getInstance().getScale();

	for(int x = 0; x < Floor::sizeX; x++)
	{
		for(int y = 0; y < Floor::sizeY; y++)
		{
			if(ar[x][y])
			{
				vertTL.texCoords = sf::Vector2f(17, 0);
				vertBL.texCoords = sf::Vector2f(17, 1);
				vertBR.texCoords = sf::Vector2f(18, 1);
				vertTR.texCoords = sf::Vector2f(18, 0);

				vertTL.position = sf::Vector2f(1 * scale + x * 6 * scale, 105 * scale + y * 4 * scale);
				vertBL.position = sf::Vector2f(1 * scale + x * 6 * scale, 108 * scale + y * 4 * scale);
				vertBR.position = sf::Vector2f(6 * scale + x * 6 * scale, 108 * scale + y * 4 * scale);
				vertTR.position = sf::Vector2f(6 * scale + x * 6 * scale, 105 * scale + y * 4 * scale);

				floor.append(vertTL);
				floor.append(vertBL);
				floor.append(vertBR);
				floor.append(vertTR);
			}
		}
	}
}

void HUD::draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(floor, &spriteSheet);

	window.draw(bomb);
	window.draw(coin);

	for(std::vector<sf::Sprite>::iterator it = hearts.begin(); it != hearts.end(); ++it)
		window.draw(*it);
}