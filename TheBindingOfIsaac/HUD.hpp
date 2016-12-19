#pragma once

#include "stdafx.h"
#include "Floor.hpp"

class HUD
{
public:
	HUD();

	void update();
	void draw(sf::RenderWindow& window);

	void constructFloor(const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& ar);
	void setCurrentRoom(int x, int y);

	static void updatePlayerCoins(int coins);
	static void updatePlayerBombs(int bombs);

private:
	void updatePlayerHealth(int health);

	sf::Texture spriteSheet;
	sf::VertexArray floor;
	sf::Sprite playerMark;
	std::vector<sf::Sprite> hearts;
	sf::Font font;
	sf::Sprite bomb;
	sf::Sprite coin;
	static sf::Text coinAmount;
	static sf::Text bombAmount;

	const int maxPlayerHealth;
	int prevPlayerHealth;
};