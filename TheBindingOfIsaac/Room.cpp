#include "stdafx.h"
#include "Room.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"

const int Room::tileSize;
const int Room::width;
const int Room::height;
sf::Texture& Room::backgroundTex = sf::Texture();
sf::Texture& Room::foregroundTex = sf::Texture();

Room::Room()
{
	backgroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
	foregroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
}

void Room::load(std::string fileName, bool upOpen, bool downOpen, bool leftOpen, bool rightOpen)
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
		for(int j = 1; j < height - 1; j++)
		{
			for(int k = 1; k < width - 1; k++)
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

	for(int x = 1; x < height - 1; x++)
	{
		for(int y = 1; y < width - 1; y++)
		{
			unsigned char tileType;
			fileStream.read(reinterpret_cast<char*>(&tileType), sizeof(char));

			tileTypes[y][x] = (TileType)tileType;
		}
	}

	#pragma region Top and bottom border
	for(int x = 0; x < width; x++)
	{
		sf::Vector2f texPosTop = sf::Vector2f(1, 1);
		sf::Vector2f texPosBot = sf::Vector2f(1, 3);
		TileType tileTypeTop = TileType::wall;
		TileType tileTypeBot = TileType::wall;

		if(x == 0)
		{
			texPosTop = sf::Vector2f(0, 1);
			texPosBot = sf::Vector2f(0, 3);
		}
		else if(x == 7)
		{
			if(upOpen)
				texPosTop = sf::Vector2f(1, 5);

			if(downOpen)
				texPosBot = sf::Vector2f(1, 4);
		}
		else if(x == 8)
		{
			if(upOpen)
			{
				texPosTop = sf::Vector2f(0, 0);
				tileTypeTop = TileType::floor;
			}

			if(downOpen)
			{
				texPosBot = sf::Vector2f(0, 0);
				tileTypeBot = TileType::floor;
			}
		}
		else if(x == 9)
		{
			if(upOpen)
				texPosTop = sf::Vector2f(0, 5);

			if(downOpen)
				texPosBot = sf::Vector2f(0, 4);
		}
		else if(x == width - 1)
		{
			texPosTop = sf::Vector2f(2, 1);
			texPosBot = sf::Vector2f(2, 3);
		}

		vertTL.texCoords = sf::Vector2f(texPosTop) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosTop.x, texPosTop.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosTop.x + 1, texPosTop.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosTop.x + 1, texPosTop.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f((float)(x + 0), 0) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f((float)(x + 0), 1) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f((float)(x + 1), 1) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f((float)(x + 1), 0) * (float)tileScreenSize;

		backgroundVertArr.append(vertTL);
		backgroundVertArr.append(vertBL);
		backgroundVertArr.append(vertBR);
		backgroundVertArr.append(vertTR);

		tileTypes[x][0] = tileTypeTop;

		vertTL.texCoords = sf::Vector2f(texPosBot) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosBot.x, texPosBot.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosBot.x + 1, texPosBot.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosBot.x + 1, texPosBot.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f((float)(x + 0), (float)(height - 1)) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f((float)(x + 0), (float)(height + 0)) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f((float)(x + 1), (float)(height + 0)) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f((float)(x + 1), (float)(height - 1)) * (float)tileScreenSize;

		backgroundVertArr.append(vertTL);
		backgroundVertArr.append(vertBL);
		backgroundVertArr.append(vertBR);
		backgroundVertArr.append(vertTR);

		tileTypes[x][height - 1] = tileTypeBot;
	}
	#pragma endregion

	#pragma region Left and right border
	for(int y = 1; y < height - 1; y++)
	{
		sf::Vector2f texPosLeft = sf::Vector2f(0, 2);
		sf::Vector2f texPosRight = sf::Vector2f(2, 2);
		TileType tileTypeLeft = TileType::wall;
		TileType tileTypeRight = TileType::wall;

		if(y == 5)
		{
			if(leftOpen)
				texPosLeft = sf::Vector2f(1, 5);
			if(rightOpen)
				texPosRight = sf::Vector2f(0, 5);
		}
		else if(y == 6)
		{
			if(leftOpen)
			{
				texPosLeft = sf::Vector2f(0, 0);
				tileTypeLeft = TileType::floor;
			}
			if(rightOpen)
			{
				texPosRight = sf::Vector2f(0, 0);
				tileTypeRight = TileType::floor;
			}
		}
		else if(y == 7)
		{
			if(leftOpen)
				texPosLeft = sf::Vector2f(1, 4);
			if(rightOpen)
				texPosRight = sf::Vector2f(0, 4);
		}

		vertTL.texCoords = sf::Vector2f(texPosLeft) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosLeft.x, texPosLeft.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosLeft.x + 1, texPosLeft.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosLeft.x + 1, texPosLeft.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f(0, (float)(y + 0)) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f(0, (float)(y + 1)) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f(1, (float)(y + 1)) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f(1, (float)(y + 0)) * (float)tileScreenSize;

		backgroundVertArr.append(vertTL);
		backgroundVertArr.append(vertBL);
		backgroundVertArr.append(vertBR);
		backgroundVertArr.append(vertTR);

		tileTypes[0][y] = tileTypeLeft;

		vertTL.texCoords = sf::Vector2f(texPosRight) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosRight.x, texPosRight.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosRight.x + 1, texPosRight.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosRight.x + 1, texPosRight.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f((float)(width - 1), (float)(y + 0)) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f((float)(width - 1), (float)(y + 1)) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f((float)(width + 0), (float)(y + 1)) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f((float)(width + 0), (float)(y + 0)) * (float)tileScreenSize;

		backgroundVertArr.append(vertTL);
		backgroundVertArr.append(vertBL);
		backgroundVertArr.append(vertBR);
		backgroundVertArr.append(vertTR);

		tileTypes[width - 1][y] = tileTypeRight;
	}
	#pragma endregion

	unsigned int count;
	fileStream.read(reinterpret_cast<char*>(&count), sizeof(int));

	for(unsigned int i = 0; i < count; i++)
	{
		unsigned int x;
		unsigned int y;
		unsigned char type;

		fileStream.read(reinterpret_cast<char*>(&x), sizeof(int));
		fileStream.read(reinterpret_cast<char*>(&y), sizeof(int));
		fileStream.read(reinterpret_cast<char*>(&type), sizeof(char));

		sf::Vector2f position = sf::Vector2f((float)x, (float)y) * (float)Utilities::getInstance().getScale();

		switch(type)
		{
			case 0:
			{
				entities.push_back(Assemblages::getInstance().createTurret(position));
				break;
			}
		}
	}

	fileStream.close();

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