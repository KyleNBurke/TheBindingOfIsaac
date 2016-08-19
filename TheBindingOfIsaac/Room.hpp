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

	static const int tileSize = 8;
	static const int width = 17;
	static const int height = 13;
	static sf::Texture& backgroundTex;
	static sf::Texture& foregroundTex;
	sf::VertexArray backgroundVertArr;
	sf::VertexArray foregroundVertArr;
	std::vector<Entity> entities;
	std::vector<Entity> addEntityQueue;
	bool complete;

private:
	std::array<std::array<TileType, height + 2>, width + 2> tileTypes;

	bool upOpen;
	bool downOpen;
	bool leftOpen;
	bool rightOpen;
};