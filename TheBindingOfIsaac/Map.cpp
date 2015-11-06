#include "stdafx.h"
#include "Map.hpp"
#include "Utilities.hpp"

std::unique_ptr<Room> Map::currentRoom;

Map::Map(HUD& hud) : vertexArray(sf::Quads), hud(hud)
{
	for(int i = 0; i < sizeX; i++)
		std::fill(map[i].begin(), map[i].end(), Room());

	clear();
}

Map::~Map()
{
	currentRoom.release();
}

void Map::generate(int seed)
{
	clear();

	std::srand(seed);

	int x = sizeX / 2;
	int y = sizeY / 2;

	activateRoom(x, y);
	
	Direction direction;
	float branchContinueChance = 1.0f;

	for(int i = 0; i < 4; i++)
	{
		int roomCount = 0;

		while(std::rand() / (float)RAND_MAX >= 1.0f - branchContinueChance)
		{
			std::vector<Direction> availableDirections;
			availableDirections = getAvialableDirections(x, y);

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
					case up:
						offY--;
						break;
					case right:
						offX++;
						break;
					case down:
						offY++;
						break;
					case left:
						offX--;
						break;
					}

					activateRoom(offX, offY);

					availableDirections.erase(std::remove(availableDirections.begin(), availableDirections.end(), direction), availableDirections.end());
				}

				if(availableDirections.size() == 1)
					direction = availableDirections[0];
				else
					direction = availableDirections[std::rand() % availableDirections.size()];
			}

			switch(direction)
			{
			case up:
				y--;
				break;
			case right:
				x++;
				break;
			case down:
				y++;
				break;
			case left:
				x--;
				break;
			}

			activateRoom(x, y);

			roomCount++;

			if(roomCount > 99)
				break;

			branchContinueChance -= 0.1f;
		}

		x = sizeX / 2;
		y = sizeY / 2;
		branchContinueChance = 1.0f;
	}
	
	map[5][3].load("RoomTest.bim");
	currentRoom = std::unique_ptr<Room>(&map[5][3]);
	hud.setMap(vertexArray);
}

void Map::clear()
{
	currentRoom.release();

	for(int i = 0; i < sizeX; i++)
		for(int j = 0; j < sizeY; j++)
			map[i][j].setActive(false);

	vertexArray.clear();
}

std::vector<Map::Direction> Map::getAvialableDirections(int x, int y)
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

		if(valid == true && yCheck - 1 != y && yCheck - 1 != -1 && map[xCheck][yCheck - 1].getActive())
			valid = false;
		if(valid == true && yCheck + 1 != y && yCheck + 1 != sizeY && map[xCheck][yCheck + 1].getActive())
			valid = false;
		if(valid == true && xCheck - 1 != x && xCheck - 1 != -1 && map[xCheck - 1][yCheck].getActive())
			valid = false;
		if(valid == true && xCheck + 1 != x && xCheck + 1 != sizeX && map[xCheck + 1][yCheck].getActive())
			valid = false;

		if(valid)
		{
			switch(i)
			{
			case 0:
				directions.push_back(Direction::up);
				break;
			case 1:
				directions.push_back(Direction::down);
				break;
			case 2:
				directions.push_back(Direction::left);
				break;
			case 3:
				directions.push_back(Direction::right);
				break;
			}
		}
	}

	return directions;
}

void Map::activateRoom(int x, int y)
{
	map[x][y].setActive(true);

	sf::Vertex vertTL;
	sf::Vertex vertBL;
	sf::Vertex vertBR;
	sf::Vertex vertTR;

	float scale = (float)Utilities::getInstance().getScale();

	vertTL.texCoords = sf::Vector2f(17, 0);
	vertBL.texCoords = sf::Vector2f(17, 1);
	vertBR.texCoords = sf::Vector2f(18, 1);
	vertTR.texCoords = sf::Vector2f(18, 0);

	vertTL.position = sf::Vector2f(1 * scale + x * 6 * scale, 97 * scale + y * 4 * scale);
	vertBL.position = sf::Vector2f(1 * scale + x * 6 * scale, 100 * scale + y * 4 * scale);
	vertBR.position = sf::Vector2f(6 * scale + x * 6 * scale, 100 * scale + y * 4 * scale);
	vertTR.position = sf::Vector2f(6 * scale + x * 6 * scale, 97 * scale + y * 4 * scale);

	vertexArray.append(vertTL);
	vertexArray.append(vertBL);
	vertexArray.append(vertBR);
	vertexArray.append(vertTR);
}

void Map::draw(sf::RenderWindow& window)
{
	currentRoom->draw(window);

	for(std::vector<sf::RectangleShape>::iterator it = shapes.begin(); it != shapes.end(); ++it)
		window.draw(*it);
}

Room& Map::getCurrentRoom()
{
	return *currentRoom;
}