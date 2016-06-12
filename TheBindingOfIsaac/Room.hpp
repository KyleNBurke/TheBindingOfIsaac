#pragma once

#include "stdafx.h"
#include <array>
#include "Utilities.hpp"
#include "Entity.hpp"

class Room
{
public:
	Room();

	static void initialize();
	void load(std::string fileName);
	void draw(sf::RenderWindow& window);

	enum TileType { floor, wall, pit };

	TileType getTileType(int x, int y);

	bool getActive() const;
	void setActive(bool active);

	static const int tileSize = 8;
	static const int width = 15;
	static const int height = 10;
	static std::vector<Entity> entities;
	static std::vector<Entity> addEntityQueue;
	static std::vector<std::unique_ptr<Entity>> removeEntityQueue;

private:
	bool active;
	sf::VertexArray backgroundVertArr;
	sf::VertexArray foregroundVertArr;
	static sf::Texture& backgroundTex;
	static sf::Texture& foregroundTex;
	std::array<std::array<TileType, height + 2>, width + 2> tileTypes;
};