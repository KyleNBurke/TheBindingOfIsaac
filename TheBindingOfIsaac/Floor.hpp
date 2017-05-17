#pragma once

#include "stdafx.h"
#include <array>
#include "Room.hpp"
#include "Utilities.hpp"

class Floor
{
public:
	Floor();

	void generate();
	void generateItems();
	static Room& getRoom(int x, int y);
	static std::shared_ptr<Room> getRoomPtr(int x, int y);
	static Room& getCurrentRoom();
	static void setCurrentRoom(int x, int y);
	static void resetPlayerComponents();

	static const int sizeX = 9;
	static const int sizeY = 5;
	static const int maxRooms = 19;
	static std::vector<int> availableRooms;
	const std::array<std::array<std::shared_ptr<Room>, sizeY>, sizeX>& getFloor() const;
	void clear(std::array<std::array<bool, sizeY>, sizeX>& ar);
	std::vector<Direction> getAvialableDirections(std::array<std::array<bool, sizeY>, sizeX>& ar, int x, int y);
	static void damagePlayer(int damage);
	static bool floorComplete;

	static Entity player;
	sf::Texture backgroundTex;
	sf::Texture foregroundTex;

private:
	static std::array<std::array<std::shared_ptr<Room>, sizeY>, sizeX> rooms;
	static std::shared_ptr<Room> currentRoom;
	static std::vector<int> loadedRooms;
};