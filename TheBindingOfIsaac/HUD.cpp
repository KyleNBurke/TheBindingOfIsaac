#include "stdafx.h"
#include "HUD.hpp"
#include "Utilities.hpp"
#include "HealthCom.hpp"
#include "GameManager.hpp"
#include "Input.hpp"

sf::Texture HUD::spriteSheet;
std::vector<sf::Sprite> HUD::hearts;
const int HUD::maxPlayerHealth = 15;
sf::Text HUD::coinAmount;
sf::Text HUD::bombAmount;
HUD::MessageType HUD::messageType;
sf::RectangleShape HUD::messageBackground;
sf::Text HUD::messageText;
sf::Sprite HUD::item;
sf::Text HUD::pressEnterText;

HUD::HUD() :
	playerMark(spriteSheet, sf::IntRect(18, 0, 5, 3)),
	bomb(spriteSheet, sf::IntRect(7, 0, 6, 8)),
	coin(spriteSheet, sf::IntRect(13, 0, 4, 4))
{
	spriteSheet.loadFromFile("Resources/HUD.png");
	floor.setPrimitiveType(sf::Quads);

	float scale = (float)Utilities::getInstance().getScale();

	playerMark.setScale(scale, scale);

	int health = std::dynamic_pointer_cast<HealthCom>(Floor::player.getComponent(Component::ComponentType::Health))->health;
	prevPlayerHealth = health;
	updatePlayerHealth(health);

	bomb.setScale(scale, scale);
	bomb.setPosition(64 * scale, 107 * scale);

	bombAmount.setFont(Utilities::getInstance().getFont());
	bombAmount.setString("00");
	bombAmount.setCharacterSize((int)scale * Room::tileSize);
	bombAmount.setPosition(73 * scale, 106 * scale);

	coin.setScale(scale, scale);
	coin.setPosition(65 * scale, 118 * scale);

	coinAmount.setFont(Utilities::getInstance().getFont());
	coinAmount.setString("00");
	coinAmount.setCharacterSize((int)scale * Room::tileSize);
	coinAmount.setPosition(73 * scale, 114 * scale);

	arrow.setScale(scale, scale);
	arrow.setTexture(spriteSheet);
	arrow.setTextureRect(sf::IntRect(23, 0, 5, 6));
	arrow.setPosition(Room::width / 2 * scale * Room::tileSize + 1.5f * scale, Room::height / 2 * scale * Room::tileSize + 1.0f * scale);

	messageBackground.setFillColor(sf::Color(50, 50, 50));
	messageBackground.setSize(sf::Vector2f(scale * Room::tileSize * 13.0f, scale * Room::tileSize * 6.0f));
	messageBackground.setPosition(scale * Room::tileSize * 2.0f, scale * Room::tileSize * 3.0f);

	messageText.setFont(Utilities::getInstance().getFont());
	messageText.setCharacterSize((int)scale * Room::tileSize);
	messageText.setPosition(scale * Room::tileSize * 2.0f + scale * 3.0f, scale * Room::tileSize * 3.0f);

	pressEnterText.setFont(Utilities::getInstance().getFont());
	pressEnterText.setString("Press enter");
	pressEnterText.setCharacterSize((int)scale * Room::tileSize);
	pressEnterText.setPosition(scale * Room::tileSize * 8.0f + scale * 4.0f, scale * Room::tileSize * 8.0f - scale * 2.0f);
}

void HUD::constructFloor(const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& ar)
{
	floor.clear();

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

void HUD::update()
{
	if(messageType != MessageType::none)
	{
		if(Input::getInstance().keyPressed(sf::Keyboard::Key::Return))
		{
			if(messageType == MessageType::dead)
				GameManager::getInstance().resetGameplay();

			messageType = none;
		}
	}
}

void HUD::draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(floor, &spriteSheet);
	window.draw(playerMark);

	window.draw(bomb);
	window.draw(bombAmount);
	window.draw(coin);
	window.draw(coinAmount);

	if(Floor::floorComplete && &Floor::getCurrentRoom() == &Floor::getRoom(Floor::sizeX / 2, Floor::sizeY / 2))
		window.draw(arrow);

	for(std::vector<sf::Sprite>::iterator it = hearts.begin(); it != hearts.end(); ++it)
		window.draw(*it);

	if(messageType != MessageType::none)
	{
		window.draw(messageBackground);
		window.draw(messageText);
		window.draw(pressEnterText);

		if(messageType == MessageType::itemPickup)
			window.draw(item);
	}
}

void HUD::setCurrentRoom(int x, int y)
{
	float scale = (float)Utilities::getInstance().getScale();

	playerMark.setPosition(scale + x * scale * 6, 105 * scale + y * scale * 4);
}

void HUD::updatePlayerHealth(int health)
{
	if(health > maxPlayerHealth)
		health = maxPlayerHealth;

	float scale = (float)Utilities::getInstance().getScale();

	hearts.clear();

	for(int i = 0; i < health; i++)
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

void HUD::updatePlayerCoins(int coins)
{
	coinAmount.setString(std::to_string(coins));
}

void HUD::updatePlayerBombs(int bombs)
{
	bombAmount.setString(std::to_string(bombs));
}

void HUD::showPickupItemMessage(Entity& entity)
{
	std::shared_ptr<ItemCom> itemCom = std::dynamic_pointer_cast<ItemCom>(entity.getComponent(Component::ComponentType::Item));

	messageType = MessageType::itemPickup;
	messageText.setString("You got:\n\n" + itemCom->description);
	item = entity.sprite;
	item.setOrigin(0.0f, 0.0f);
	int scale = Utilities::getInstance().getScale();
	item.setPosition(scale * Room::tileSize * 7.0f, scale * Room::tileSize * 3.0f + scale);
}

void HUD::showNewLevelMessage(int level)
{
	messageType = MessageType::newLevel;
	messageText.setString("Level: " + std::to_string(level) +"\nUse WASD to move\nUse IJKL to shoot\nUse E to place a bomb");
}

void HUD::showFloorCompeteMessage()
{
	messageType = MessageType::floorComplete;
	messageText.setString("Floor complete!");
}

void HUD::showDeadMessage()
{
	messageType = MessageType::dead;
	messageText.setString("You have died");
}