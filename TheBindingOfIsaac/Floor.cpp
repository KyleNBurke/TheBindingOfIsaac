#include "stdafx.h"
#include "Floor.hpp"
#include "Assemblages.hpp"

#include "ItemCom.hpp"
#include "HUD.hpp"
#include "HealthCom.hpp"

std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX> Floor::rooms;
std::shared_ptr<Room> Floor::currentRoom;
Entity Floor::player(Assemblages::getInstance().createPlayer(sf::Vector2f(Utilities::getInstance().getScale() * Room::tileSize * Room::width / 2.0f, 
	Utilities::getInstance().getScale() * Room::tileSize * Room::height / 2.0f)));
std::vector<int> Floor::availableRooms;
bool Floor::floorComplete = false;
std::vector<int> Floor::loadedRooms;

Floor::Floor()
{
	backgroundTex.loadFromFile("Resources/Background.png");
	foregroundTex.loadFromFile("Resources/Foreground.png");
	Room::backgroundTex = backgroundTex;
	Room::foregroundTex = foregroundTex;

	for(int i = 1; i <= maxRooms; i++)
		availableRooms.push_back(i);
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

	rooms[4][2]->complete = true;
	rooms[4][2]->load("Rooms/MainRoom.bim");
	currentRoom = std::shared_ptr<Room>(rooms[4][2]);

	generateItems();
	loadedRooms.clear();
}

void Floor::generateItems()
{
	float size = (float)Utilities::getInstance().getScale() * Room::tileSize;

	rooms[4][2]->addEntity(Assemblages::getInstance().createROF_UpItem(sf::Vector2f(size * 3.5f, size * 1.5f)));
	rooms[4][2]->addEntity(Assemblages::getInstance().createPlusTenBombsItem(sf::Vector2f(size * 5.5f, size * 1.5f)));
	rooms[4][2]->addEntity(Assemblages::getInstance().createRangeUpItem(sf::Vector2f(size * 10.5f, size * 1.5f)));
	rooms[4][2]->addEntity(Assemblages::getInstance().createProjectileBombsItem(sf::Vector2f(size * 12.5f, size * 1.5f)));
	rooms[4][2]->addEntity(Assemblages::getInstance().createPlusOneHeartItem(sf::Vector2f(size * 11.5f, size * 6.5f)));
	rooms[4][2]->addEntity(Assemblages::getInstance().createPlusOneBomb(sf::Vector2f(size * 5.5f, size * 6.5f)));
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
			rooms[x][y].reset();
		}
	}
}


std::vector<Direction> Floor::getAvialableDirections(std::array<std::array<bool, sizeY>, sizeX>& ar, int x, int y)
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

void Floor::damagePlayer(int damage)
{
	getCurrentRoom().addEntity(Assemblages::getInstance().createPlayerDamageStain(Floor::player.sprite.getPosition()));
	std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(player.getComponent(Component::ComponentType::Health));
	healthCom->health -= damage;
	healthCom->flashing = true;
	HUD::updatePlayerHealth(healthCom->health);

	if(healthCom->health <= 0) {
		HUD::showDeadMessage();
	}
}

const std::array<std::array<std::shared_ptr<Room>, Floor::sizeY>, Floor::sizeX>& Floor::getFloor() const
{
	return rooms;
}

Room& Floor::getRoom(int x, int y)
{
	return *rooms[x][y];
}

std::shared_ptr<Room> Floor::getRoomPtr(int x, int y)
{
	return rooms[x][y];
}

Room& Floor::getCurrentRoom()
{
	return *currentRoom;
}

void Floor::setCurrentRoom(int x, int y)
{
	if(!rooms[x][y]->complete)
	{
		//rooms[x][y]->load("Rooms/19.bim");

		if(availableRooms.size() == 0)
			for(int i = 1; i <= maxRooms; i++)
				availableRooms.push_back(i);

		int roomIndex = rand() % availableRooms.size();

		if(loadedRooms.size() < maxRooms - 4)
			while(std::find(loadedRooms.begin(), loadedRooms.end(), roomIndex) != loadedRooms.end())
				roomIndex = rand() % availableRooms.size();

		int room = availableRooms[roomIndex];
		availableRooms.erase(availableRooms.begin() + roomIndex);

		std::cout << "loading room: " << room << std::endl;
		rooms[x][y]->load("Rooms/" + std::to_string(room) + ".bim");

		loadedRooms.push_back(roomIndex);
	}

	currentRoom = std::shared_ptr<Room>(rooms[x][y]);
}

void Floor::resetPlayerComponents()
{
	player.components.clear();
	sf::Vector2f position(Utilities::getInstance().getScale() * Room::tileSize * Room::width / 2.0f,
		Utilities::getInstance().getScale() * Room::tileSize * Room::height / 2.0f);
	player = Assemblages::getInstance().createPlayer(position);
}