#pragma once

#include "stdafx.h"
#include <array>
#include "Utilities.hpp"
#include "Entity.hpp"

class Room
{
public:
	Room(bool upOpen, bool downOpen, bool leftOpen, bool rightOpen);
	void load(std::string fileName);

	enum TileType { floor, wall, pit };

	TileType getTileType(int x, int y);
	void addEntity(Entity entity);
	void killEnemy(Entity& entity);
	std::vector<Entity>::iterator removeEntity(std::vector<Entity>::iterator& entityIt);
	std::vector<Entity>& getEntities();
	std::vector<Entity>& getAddEntityQueue();
	void drawForeground(sf::RenderWindow& window);
	void drawBackground(sf::RenderWindow& window);

	static const int tileSize = 8;
	static const int width = 17;
	static const int height = 13;
	static sf::Texture& backgroundTex;
	static sf::Texture& foregroundTex;
	bool complete;
	int enemies;

private:
	std::array<std::array<TileType, height + 2>, width + 2> tileTypes;
	std::vector<Entity> entities;
	std::vector<Entity> addEntityQueue;

	sf::VertexArray backgroundVertArr;
	sf::VertexArray foregroundVertArr;
	bool upOpen;
	bool downOpen;
	bool leftOpen;
	bool rightOpen;
	sf::Sprite upBlock;
	sf::Sprite downBlock;
	sf::Sprite leftBlock;
	sf::Sprite rightBlock;
};