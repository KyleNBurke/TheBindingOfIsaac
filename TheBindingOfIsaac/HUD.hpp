#pragma once

#include "stdafx.h"
#include "Floor.hpp"
#include "ItemCom.hpp"

class HUD
{
public:
	HUD();

	void update();
	void draw(sf::RenderWindow& window);

	void constructFloor(const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& ar);
	void setCurrentRoom(int x, int y);

	static void updatePlayerHealth(int health);
	static void updatePlayerCoins(int coins);
	static void updatePlayerBombs(int bombs);
	static void showPickupItemMessage(Entity& entity);
	static void showNewLevelMessage(int level);

private:
	static sf::Texture spriteSheet;
	sf::VertexArray floor;
	sf::Sprite playerMark;
	static std::vector<sf::Sprite> hearts;
	sf::Sprite bomb;
	sf::Sprite coin;
	static sf::Text coinAmount;
	static sf::Text bombAmount;
	static const int maxPlayerHealth;
	int prevPlayerHealth;
	
	enum MessageType {
		none,
		itemPickup,
		newLevel
	};

	static MessageType messageType;
	static sf::RectangleShape messageBackground;
	static sf::Text messageText;
	static sf::Sprite item;
	static sf::Text pressEnterText;
};