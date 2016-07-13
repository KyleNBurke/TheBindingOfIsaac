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

void Floor::generate()
{
	std::array<std::array<bool, sizeY>, sizeX> ar;

	clear(ar);

	int x = sizeX / 2;
	int y = sizeY / 2;

	ar[x][y] = true;

	Direction direction;
	float branchContinueChance = 1.0f;

	for(int i = 0; i < 4; i++)
	{
		int roomCount = 0;

		while(std::rand() / (float)RAND_MAX >= 1.0f - branchContinueChance)
		{
			std::vector<Direction> availableDirections;
			availableDirections = getAvialableDirections(ar, x, y);

			if(availableDirections.size() == 0)
				break;
			else if(availableDirections.size() == 1)
				direction = availableDirections[0];
			else
			{
				if(roomCount > 1 && std::rand() / (float)RAND_MAX >= 0.5)
				{
					direction = availableDirections[std::rand() % availableDirections.size()];

					int offX = x;
					int offY = y;

					switch(direction)
					{
					case Up:
						offY--;
						break;
					case Right:
						offX++;
						break;
					case Down:
						offY++;
						break;
					case Left:
						offX--;
						break;
					}

					ar[offX][offY] = true;

					availableDirections.erase(std::remove(availableDirections.begin(), availableDirections.end(), direction), availableDirections.end());
				}

				if(availableDirections.size() == 1)
					direction = availableDirections[0];
				else
					direction = availableDirections[std::rand() % availableDirections.size()];
			}

			switch(direction)
			{
			case Up:
				y--;
				break;
			case Right:
				x++;
				break;
			case Down:
				y++;
				break;
			case Left:
				x--;
				break;
			}

			ar[x][y] = true;

			roomCount++;

			if(roomCount > 99)
				break;

			branchContinueChance -= 0.1f;
		}

		x = sizeX / 2;
		y = sizeY / 2;
		branchContinueChance = 1.0f;
	}

	for(int x = 0; x < sizeX; x++)
	{
		for(int y = 0; y < sizeY; y++)
		{
			if(ar[x][y])
			{
				bool u = false, d = false, l = false, r = false;
				if(y != 0 && ar[x][y - 1])
					u = true;
				if(y != sizeY - 1 && ar[x][y + 1])
					d = true;
				if(x != 0 && ar[x - 1][y])
					l = true;
				if(x != sizeX - 1 && ar[x + 1][y])
					r = true;

				rooms[x][y] = std::shared_ptr<Room>(new Room(u, d, l, r));
			}
		}
	}



	/*rooms[4][2] = std::shared_ptr<Room>(new Room(true, true, true, true)); //middle
	rooms[4][1] = std::shared_ptr<Room>(new Room(false, true, false, false)); //up
	rooms[4][3] = std::shared_ptr<Room>(new Room(true, false, false, false)); //down
	rooms[3][2] = std::shared_ptr<Room>(new Room(false, false, false, true)); //Left
	rooms[5][2] = std::shared_ptr<Room>(new Room(false, false, true, false)); //Right*/

	//rooms[4][2] = std::shared_ptr<Room>(new Room(false, false, false, false));
	rooms[4][2]->load("Rooms/MainRoom.bim");
	currentRoom = std::shared_ptr<Room>(rooms[4][2]);
	playerPosX = 4;
	playerPosY = 2;
}

void Floor::clear(std::array<std::array<bool, sizeY>, sizeX>& ar)
{
	/*for(int i = 0; i < sizeX; i++)
	{
		std::fill_n(rooms[i], sizeY, 0);
		std::fill_n(ar[i], sizeY, false);

	}*/

	for(int x = 0; x < sizeX; x++)
	{
		for(int y = 0; y < sizeY; y++)
		{
			ar[x][y] = false;
		}
	}
}


std::vector<Floor::Direction> Floor::getAvialableDirections(std::array<std::array<bool, sizeY>, sizeX>& ar, int x, int y)
{
	std::vector<Direction> directions;
	int xCheck = x;
	int yCheck = y;

	for(int i = 0; i < 4; i++)
	{
		switch(i)
		{
		case 0:
			xCheck = x;
			yCheck = y - 1;
			break;
		case 1:
			xCheck = x;
			yCheck = y + 1;
			break;
		case 2:
			xCheck = x - 1;
			yCheck = y;
			break;
		case 3:
			xCheck = x + 1;
			yCheck = y;
			break;
		}

		bool valid = true;

		if(yCheck == -1 || yCheck == sizeY || xCheck == -1 || xCheck == sizeX)
			valid = false;

		if(valid == true && yCheck - 1 != y && yCheck - 1 != -1 && ar[xCheck][yCheck - 1])
			valid = false;
		if(valid == true && yCheck + 1 != y && yCheck + 1 != sizeY && ar[xCheck][yCheck + 1])
			valid = false;
		if(valid == true && xCheck - 1 != x && xCheck - 1 != -1 && ar[xCheck - 1][yCheck])
			valid = false;
		if(valid == true && xCheck + 1 != x && xCheck + 1 != sizeX && ar[xCheck + 1][yCheck])
			valid = false;

		if(valid)
		{
			switch(i)
			{
			case 0:
				directions.push_back(Direction::Up);
				break;
			case 1:
				directions.push_back(Direction::Down);
				break;
			case 2:
				directions.push_back(Direction::Left);
				break;
			case 3:
				directions.push_back(Direction::Right);
				break;
			}
		}
	}

	return directions;
}

const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& Floor::getFloor() const
{
	return rooms;
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
		player.sprite.setPosition((float)(Room::width * scale) / 2 - player.sprite.getGlobalBounds().width / 2, (float)(Room::height - 1) * scale);
		break;
	case Down:
		playerPosY++;
		player.sprite.setPosition((float)(Room::width * scale) / 2 - player.sprite.getGlobalBounds().width / 2, scale - player.sprite.getGlobalBounds().height);
		break;
	case Left:
		playerPosX--;
		player.sprite.setPosition((float)(Room::width - 1) * scale, (float)(Room::height * scale) / 2 - player.sprite.getGlobalBounds().height / 2);
		break;
	case Right:
		playerPosX++;
		player.sprite.setPosition(scale - player.sprite.getGlobalBounds().width, (float)(Room::height * scale) / 2 - player.sprite.getGlobalBounds().height / 2);
		break;
	}

	if(!rooms[playerPosX][playerPosY]->complete)
	{
		rooms[playerPosX][playerPosY]->load("Rooms/" + std::to_string(rand() % maxRooms + 1) + ".bim");
	}

	currentRoom = std::shared_ptr<Room>(rooms[playerPosX][playerPosY]);
}