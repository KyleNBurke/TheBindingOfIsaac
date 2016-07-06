#pragma once

#include "stdafx.h"
#include <array>
#include "Utilities.hpp"
#include "Entity.hpp"

class Room
{
public:
	Room();
	void load(std::string fileName, bool upOpen, bool downOpen, bool leftOpen, bool rightOpen);
	void draw(sf::RenderWindow& window);

	enum TileType { floor, wall, pit };

	TileType getTileType(int x, int y);

	static const int tileSize = 8;
	static const int width = 17;
	static const int height = 13;
	static sf::Texture& backgroundTex;
	static sf::Texture& foregroundTex;
	std::vector<Entity> entities;
	std::vector<Entity> addEntityQueue;

private:
	sf::VertexArray backgroundVertArr;
	sf::VertexArray foregroundVertArr;
	std::array<std::array<TileType, height + 2>, width + 2> tileTypes;
};