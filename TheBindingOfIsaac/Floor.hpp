#pragma once

#include "stdafx.h"
#include <array>
#include "Room.hpp"

class Floor
{
public:
	Floor();

	void generate();
	void draw(sf::RenderWindow& window);
	static Room& getCurrentRoom();
	enum Direction {Up, Down, Left, Right};
	static void transitionRoom(Direction direction);

	static const int sizeX = 9;
	static const int sizeY = 5;
	static const int maxRooms = 4;
	const std::array<std::array<std::shared_ptr<Room>, sizeY>, sizeX>& getFloor() const;
	void clear(std::array<std::array<bool, sizeY>, sizeX>& ar);
	std::vector<Direction> getAvialableDirections(std::array<std::array<bool, sizeY>, sizeX>& ar, int x, int y);
	static Entity player;
	static int playerPosX;
	static int playerPosY;
	sf::Texture backgroundTex;
	sf::Texture foregroundTex;

private:
	static std::array<std::array<std::shared_ptr<Room>, sizeY>, sizeX> rooms;
	static std::shared_ptr<Room> currentRoom;
};