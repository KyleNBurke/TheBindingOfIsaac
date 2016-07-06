#include "stdafx.h"
#include "Floor.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"

std::shared_ptr<Room> Floor::currentRoom;
Entity Floor::player(Assemblages::getInstance().createPlayer());

Floor::Floor()
{
	backgroundTex.loadFromFile("Background.png");
	foregroundTex.loadFromFile("Foreground.png");
	Room::backgroundTex = backgroundTex;
	Room::foregroundTex = foregroundTex;
}

void Floor::generate(int seed)
{
	rooms[4][2] = std::shared_ptr<Room>(new Room()); //middle
	rooms[4][1] = std::shared_ptr<Room>(new Room()); //up
	rooms[4][3] = std::shared_ptr<Room>(new Room()); //down
	rooms[3][2] = std::shared_ptr<Room>(new Room()); //left
	rooms[5][2] = std::shared_ptr<Room>(new Room()); //right

	rooms[4][2]->load("Rooms/RoomTest.bim", true, true, true, true);
	currentRoom = std::shared_ptr<Room>(rooms[4][2]);
}

void Floor::draw(sf::RenderWindow& window)
{
	currentRoom->draw(window);
}

Room& Floor::getCurrentRoom()
{
	return *currentRoom;
}