#include "stdafx.h"
#include "Room.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"

sf::Texture& Room::backgroundTex = sf::Texture();
sf::Texture& Room::foregroundTex = sf::Texture();
const int Room::tileSize;
const int Room::width;
const int Room::height;

Room::Room() : active(false)
{
	backgroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
	foregroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
}

void Room::initialize()
{
	backgroundTex.loadFromFile("Background.png");
	foregroundTex.loadFromFile("Foreground.png");
}

void Room::load(std::string fileName)
{
	std::ifstream fileStream;
	fileStream.open(fileName, std::ios::in | std::ios::binary);

	const int tileTexSize = tileSize;
	const int tileScreenSize = tileTexSize * Utilities::getInstance().getScale();

	sf::Vertex vertTL;
	sf::Vertex vertBL;
	sf::Vertex vertBR;
	sf::Vertex vertTR;

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < height; j++)
		{
			for(int k = 0; k < width; k++)
			{
				unsigned char tile;
				fileStream.read(reinterpret_cast<char*>(&tile), sizeof(char));

				if(tile == 0)
					continue;

				tile--;
				int tilesInTexture = i == 0 ? backgroundTex.getSize().x / tileTexSize : foregroundTex.getSize().x / tileTexSize;
				sf::Vector2f texPos((float)(tile % tilesInTexture) * tileTexSize, (float)std::floor(tile / tilesInTexture) * tileTexSize);

				vertTL.texCoords = sf::Vector2f(texPos);
				vertBL.texCoords = sf::Vector2f(texPos.x, texPos.y + tileTexSize);
				vertBR.texCoords = sf::Vector2f(texPos.x + tileTexSize, texPos.y + tileTexSize);
				vertTR.texCoords = sf::Vector2f(texPos.x + tileTexSize, texPos.y);

				vertTL.position = sf::Vector2f((float)(k + 0) * tileScreenSize, (float)(j + 0) * tileScreenSize);
				vertBL.position = sf::Vector2f((float)(k + 0) * tileScreenSize, (float)(j + 1) * tileScreenSize);
				vertBR.position = sf::Vector2f((float)(k + 1) * tileScreenSize, (float)(j + 1) * tileScreenSize);
				vertTR.position = sf::Vector2f((float)(k + 1) * tileScreenSize, (float)(j + 0) * tileScreenSize);

				if(i == 0)
				{
					backgroundVertArr.append(vertTL);
					backgroundVertArr.append(vertBL);
					backgroundVertArr.append(vertBR);
					backgroundVertArr.append(vertTR);
				}
				else
				{
					foregroundVertArr.append(vertTL);
					foregroundVertArr.append(vertBL);
					foregroundVertArr.append(vertBR);
					foregroundVertArr.append(vertTR);
				}
			}
		}
	}

	for(int x = 0; x < height; x++)
	{
		for(int y = 0; y < width; y++)
		{
			unsigned char tileType;
			fileStream.read(reinterpret_cast<char*>(&tileType), sizeof(char));

			tileTypes[y][x] = (TileType)tileType;
		}
	}

	fileStream.close();

	active = true;

	//Read file for entities...
	//entities.push_back(Assemblages::getInstance().createTurret(sf::Vector2f(800.0f, 500.0f)));
	//entities.push_back(Assemblages::getInstance().createBouncer(sf::Vector2f(500.f, 200.0f), sf::Vector2f(std::sqrt(0.5f), std::sqrt(0.5f))));
}

Room::TileType Room::getTileType(int x, int y)
{
	return tileTypes[x][y];
}

void Room::draw(sf::RenderWindow& window)
{
	window.draw(backgroundVertArr, &backgroundTex);
	window.draw(foregroundVertArr, &foregroundTex);
}

bool Room::getActive() const
{
	return active;
}

void Room::setActive(bool active)
{
	this->active = active;
}