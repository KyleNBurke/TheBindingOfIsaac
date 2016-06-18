#include "stdafx.h"
#include "Room.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"

sf::Texture& Room::backgroundTex = sf::Texture();
sf::Texture& Room::foregroundTex = sf::Texture();
const int Room::tileSize;
const int Room::width;
const int Room::height;
std::vector<Entity> Room::entities;
std::vector<Entity> Room::addEntityQueue;

Room::Room() : active(false)
{
	backgroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
	foregroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
}

void Room::initialize()
{
	backgroundTex.loadFromFile("Background.png");
	foregroundTex.loadFromFile("Foreground.png");

	entities.push_back(Assemblages::getInstance().createPlayer());
	entities.push_back(Assemblages::getInstance().createTurret(sf::Vector2f(800.0f, 500.0f)));
}

void Room::load(std::string fileName)
{
	std::ifstream fileStream;
	fileStream.open(fileName, std::ios::in | std::ios::binary);

	const int width = 15; //move these somewhere else
	const int height = 10;

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
				const int tilesInTexture = i == 0 ? backgroundTex.getSize().x / tileTexSize : foregroundTex.getSize().x / tileTexSize;
				sf::Vector2f texPos((float)(tile % tilesInTexture) * tileTexSize, (float)std::floor(tile / tilesInTexture) * tileTexSize);

				vertTL.texCoords = sf::Vector2f(texPos);
				vertBL.texCoords = sf::Vector2f(texPos.x, texPos.y + tileTexSize);
				vertBR.texCoords = sf::Vector2f(texPos.x + tileTexSize, texPos.y + tileTexSize);
				vertTR.texCoords = sf::Vector2f(texPos.x + tileTexSize, texPos.y);

				vertTL.position = sf::Vector2f((float)(k + 1) * tileScreenSize, (float)(j + 1) * tileScreenSize);
				vertBL.position = sf::Vector2f((float)(k + 1) * tileScreenSize, (float)(j + 2) * tileScreenSize);
				vertBR.position = sf::Vector2f((float)(k + 2) * tileScreenSize, (float)(j + 2) * tileScreenSize);
				vertTR.position = sf::Vector2f((float)(k + 2) * tileScreenSize, (float)(j + 1) * tileScreenSize);

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

			tileTypes[y + 1][x + 1] = (TileType)tileType;
		}
	}

#pragma region add border tiles
		vertTL.texCoords = sf::Vector2f(8.0f, 0.0f);
		vertBL.texCoords = sf::Vector2f(8.0f, 8.0f);
		vertBR.texCoords = sf::Vector2f(16.0f, 8.0f);
		vertTR.texCoords = sf::Vector2f(16.0f, 0.0f);

		for(int x = 0; x < width + 2; x++)
		{
			vertTL.position = sf::Vector2f((float)x * tileScreenSize, 0.0f);
			vertBL.position = sf::Vector2f((float)x * tileScreenSize, (float)tileScreenSize);
			vertBR.position = sf::Vector2f((float)(x + 1) * tileScreenSize, (float)tileScreenSize);
			vertTR.position = sf::Vector2f((float)(x + 1) * tileScreenSize, 0.0f);

			backgroundVertArr.append(vertTL);
			backgroundVertArr.append(vertBL);
			backgroundVertArr.append(vertBR);
			backgroundVertArr.append(vertTR);

			vertTL.position = sf::Vector2f((float)x * tileScreenSize, (float)(height + 1) * tileScreenSize);
			vertBL.position = sf::Vector2f((float)x * tileScreenSize, (float)(height + 2) * tileScreenSize);
			vertBR.position = sf::Vector2f((float)(x + 1) * tileScreenSize, (float)(height + 2) * tileScreenSize);
			vertTR.position = sf::Vector2f((float)(x + 1) * tileScreenSize, (float)(height + 1) * tileScreenSize);

			backgroundVertArr.append(vertTL);
			backgroundVertArr.append(vertBL);
			backgroundVertArr.append(vertBR);
			backgroundVertArr.append(vertTR);

			tileTypes[x][0] = TileType::wall;
			tileTypes[x][height + 1] = TileType::wall;
		}

		for(int y = 1; y < height + 1; y++)
		{
			vertTL.position = sf::Vector2f(0.0f, (float)y * tileScreenSize);
			vertBL.position = sf::Vector2f(0.0f, (float)(y + 1) * tileScreenSize);
			vertBR.position = sf::Vector2f((float)tileScreenSize, (float)(y + 1) * tileScreenSize);
			vertTR.position = sf::Vector2f((float)tileScreenSize, (float)y * tileScreenSize);

			backgroundVertArr.append(vertTL);
			backgroundVertArr.append(vertBL);
			backgroundVertArr.append(vertBR);
			backgroundVertArr.append(vertTR);

			vertTL.position = sf::Vector2f((float)(width + 1) * tileScreenSize, (float)y * tileScreenSize);
			vertBL.position = sf::Vector2f((float)(width + 1) * tileScreenSize, (float)(y + 1) * tileScreenSize);
			vertBR.position = sf::Vector2f((float)(width + 2) * tileScreenSize, (float)(y + 1) * tileScreenSize);
			vertTR.position = sf::Vector2f((float)(width + 2) * tileScreenSize, (float)y * tileScreenSize);

			backgroundVertArr.append(vertTL);
			backgroundVertArr.append(vertBL);
			backgroundVertArr.append(vertBR);
			backgroundVertArr.append(vertTR);

			tileTypes[0][y] = TileType::wall;
			tileTypes[width + 1][y] = TileType::wall;
		}
#pragma endregion

	fileStream.close();

	active = true;
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