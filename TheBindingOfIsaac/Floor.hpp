#pragma once

#include "stdafx.h"
#include <array>
#include "Room.hpp"

class Floor
{
public:
	Floor();

	void generate(int seed);
	void draw(sf::RenderWindow& window);
	static Room& getCurrentRoom();

	static const int sizeX = 9;
	static const int sizeY = 5;
	static Entity player;
	sf::Texture backgroundTex;
	sf::Texture foregroundTex;

private:
	std::array<std::array<std::shared_ptr<Room>, sizeY>, sizeX> rooms;
	static std::shared_ptr<Room> currentRoom;
};