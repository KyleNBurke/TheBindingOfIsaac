#pragma once

#include "stdafx.h"
#include <array>
#include "Room.hpp"
#include "HUD.hpp"

class Map
{
public:
	Map(HUD& hud);
	~Map(); //Rule of threes?

	void generate(int seed);
	void draw(sf::RenderWindow& window);
	static Room& getCurrentRoom();

	static const int sizeX = 9;
	static const int sizeY = 5;

private:
	enum Direction { up, down, left, right };

	std::vector<Direction> getAvialableDirections(int x, int y);
	void clear();
	void activateRoom(int x, int y);
	
	std::array<std::array<Room, sizeY>, sizeX> map;
	static std::unique_ptr<Room> currentRoom;
	sf::VertexArray vertexArray;
	HUD& hud;

	std::vector<sf::RectangleShape> shapes;
};