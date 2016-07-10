#include "stdafx.h"
#include "Floor.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"

int Floor::playerPosX;
int Floor::playerPosY;
std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX> Floor::rooms;
std::shared_ptr<Room> Floor::currentRoom;
Entity Floor::player(Assemblages::getInstance().createPlayer(sf::Vector2f(200.0f, 200.0f)));

Floor::Floor()
{
	backgroundTex.loadFromFile("Resources/Background.png");
	foregroundTex.loadFromFile("Resources/Foreground.png");
	Room::backgroundTex = backgroundTex;
	Room::foregroundTex = foregroundTex;
}

void Floor::generate(int seed)
{
	rooms[4][2] = std::shared_ptr<Room>(new Room()); //middle
	rooms[4][1] = std::shared_ptr<Room>(new Room()); //up

	rooms[4][2]->load("Rooms/RoomTest.bim", true, false, false, false);
	rooms[4][1]->load("Rooms/RoomTestUp.bim", false, true, false, false);
	currentRoom = std::shared_ptr<Room>(rooms[4][2]);
	playerPosX = 4;
	playerPosY = 2;
}

void Floor::draw(sf::RenderWindow& window)
{
	currentRoom->draw(window);
}

Room& Floor::getCurrentRoom()
{
	return *currentRoom;
}

void Floor::transitionRoom(Direction direction)
{
	int scale = Utilities::getInstance().getScale() * Room::tileSize;

	switch(direction)
	{
	case Up:
		playerPosY--;
		currentRoom = std::shared_ptr<Room>(rooms[playerPosX][playerPosY]);
		player.sprite.setPosition((float)(Room::width * scale) / 2 - player.sprite.getGlobalBounds().width / 2, (float)(Room::height - 1) * scale);
		break;
	case Down:
		playerPosY++;
		currentRoom = std::shared_ptr<Room>(rooms[playerPosX][playerPosY]);
		player.sprite.setPosition((float)(Room::width * scale) / 2 - player.sprite.getGlobalBounds().width / 2, scale - player.sprite.getGlobalBounds().height);
		break;
	case Left:
		playerPosX--;
		currentRoom = std::shared_ptr<Room>(rooms[playerPosX][playerPosY]);
		player.sprite.setPosition((float)(Room::width - 1) * scale, (float)(Room::height * scale) / 2 - player.sprite.getGlobalBounds().height / 2);
		break;
	case Right:
		playerPosX++;
		currentRoom = std::shared_ptr<Room>(rooms[playerPosX][playerPosY]);
		player.sprite.setPosition(scale - player.sprite.getGlobalBounds().width, (float)(Room::height * scale) / 2 - player.sprite.getGlobalBounds().height / 2);
		break;
	}
}