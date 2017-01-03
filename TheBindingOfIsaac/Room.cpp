#include "stdafx.h"
#include "Room.hpp"
#include "Utilities.hpp"
#include "Assemblages.hpp"
#include "BouncerCom.hpp"
#include "GameplayState.hpp"
#include "FlyMoveCom.hpp"

const int Room::tileSize;
const int Room::width;
const int Room::height;
sf::Texture& Room::backgroundTex = sf::Texture();
sf::Texture& Room::foregroundTex = sf::Texture();

Room::Room(bool upOpen, bool downOpen, bool leftOpen, bool rightOpen) : 
	upOpen(upOpen), downOpen(downOpen), leftOpen(leftOpen), rightOpen(rightOpen), complete(false), enemies(0)
{
	backgroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
	foregroundVertArr.setPrimitiveType(sf::PrimitiveType::Quads);
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
				texPosTop = sf::Vector2f(0, 0);

			if(downOpen)
				texPosBot = sf::Vector2f(0, 0);
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

		if(x == 8 && upOpen)
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

		tileTypes[x][0] = tileTypeTop;

		vertTL.texCoords = sf::Vector2f(texPosBot) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosBot.x, texPosBot.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosBot.x + 1, texPosBot.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosBot.x + 1, texPosBot.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f((float)(x + 0), (float)(height - 1)) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f((float)(x + 0), (float)(height + 0)) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f((float)(x + 1), (float)(height + 0)) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f((float)(x + 1), (float)(height - 1)) * (float)tileScreenSize;

		if(x == 8 && downOpen)
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
				texPosLeft = sf::Vector2f(0, 0);
			if(rightOpen)
				texPosRight = sf::Vector2f(0, 0);
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

		if(y == 6 && leftOpen)
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

		tileTypes[0][y] = tileTypeLeft;

		vertTL.texCoords = sf::Vector2f(texPosRight) * (float)tileTexSize;
		vertBL.texCoords = sf::Vector2f(texPosRight.x, texPosRight.y + 1) * (float)tileTexSize;
		vertBR.texCoords = sf::Vector2f(texPosRight.x + 1, texPosRight.y + 1) * (float)tileTexSize;
		vertTR.texCoords = sf::Vector2f(texPosRight.x + 1, texPosRight.y) * (float)tileTexSize;

		vertTL.position = sf::Vector2f((float)(width - 1), (float)(y + 0)) * (float)tileScreenSize;
		vertBL.position = sf::Vector2f((float)(width - 1), (float)(y + 1)) * (float)tileScreenSize;
		vertBR.position = sf::Vector2f((float)(width + 0), (float)(y + 1)) * (float)tileScreenSize;
		vertTR.position = sf::Vector2f((float)(width + 0), (float)(y + 0)) * (float)tileScreenSize;

		if(y == 6 && rightOpen)
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

		float scale = (float)Utilities::getInstance().getScale();
		sf::Vector2f position = sf::Vector2f((float)x, (float)y) * scale + sf::Vector2f((float)tileScreenSize, (float)tileScreenSize);

		switch(type)
		{
			/*
			0 - Bouncer
			1 - Direct Jimmy
			2 - Round Jimmy
			3 - Attack Fly
			4 - Bomb Fly
			5 - Daddy Fly
			6 - Attack Fly Spawner
			7 - Bomb Fly Spawner
			8 - Random Dashie
			9 - Direct Dashie
			10 - Spinny
			11 - Bomb Spinny
			12 - Walker
			13 - Round Shot Walker
			14 - Fast Walker
			*/

			case 0:
				addEntity(Assemblages::getInstance().createBouncer(position));
				break;
			case 1:
				addEntity(Assemblages::getInstance().createDirectJimmy(position));
				break;
			case 2:
				addEntity(Assemblages::getInstance().createRoundJimmy(position));
				break;
			case 3:
				addEntity(Assemblages::getInstance().createAttackFly(position));
				break;
			case 4:
				addEntity(Assemblages::getInstance().createBombFly(position));
				break;
			case 5:
				addEntity(Assemblages::getInstance().createDaddyFly(position));
				break;
			case 6:
				addEntity(Assemblages::getInstance().createAttackFlySpawner(position));
				break;
			case 7:
				addEntity(Assemblages::getInstance().createBombFlySpawner(position));
				break;
			case 8:
				addEntity(Assemblages::getInstance().createRandomDashie(position));
				break;
			case 9:
				addEntity(Assemblages::getInstance().createDirectDashie(position));
				break;
			case 10:
				addEntity(Assemblages::getInstance().createSpinny(position));
				break;
			case 11:
				addEntity(Assemblages::getInstance().createBombSpinny(position));
				break;
			case 12:
				addEntity(Assemblages::getInstance().createWalker(position));
				break;
			case 13:
				addEntity(Assemblages::getInstance().createRoundShotWalker(position));
				break;
			case 14:
				addEntity(Assemblages::getInstance().createFastWalker(position));
				break;
		}
	}

	fileStream.close();

	float scale = (float)Utilities::getInstance().getScale();
	if(upOpen)
	{
		upBlock = sf::Sprite(foregroundTex, sf::IntRect(0, 0, tileSize, tileSize));
		upBlock.setPosition(8.0f * (float)tileScreenSize, 0.0f);
		upBlock.setScale(scale, scale);

		if(complete)
			tileTypes[8][0] = TileType::floor;
	}
	if(downOpen)
	{
		downBlock = sf::Sprite(foregroundTex, sf::IntRect(0, 0, tileSize, tileSize));
		downBlock.setPosition(8.0f * (float)tileScreenSize, (height - 1) * (float)tileScreenSize);
		downBlock.setScale(scale, scale);

		if(complete)
			tileTypes[8][height - 1] = TileType::floor;
	}
	if(leftOpen)
	{
		leftBlock = sf::Sprite(foregroundTex, sf::IntRect(0, 0, tileSize, tileSize));
		leftBlock.setPosition(0.0f, 6.0f * (float)tileScreenSize);
		leftBlock.setScale(scale, scale);

		if(complete)
			tileTypes[0][6] = TileType::floor;
	}
	if(rightOpen)
	{
		rightBlock = sf::Sprite(foregroundTex, sf::IntRect(0, 0, tileSize, tileSize));
		rightBlock.setPosition((width - 1) * (float)tileScreenSize, 6.0f * (float)tileScreenSize);
		rightBlock.setScale(scale, scale);

		if(complete)
			tileTypes[width - 1][6] = TileType::floor;
	}


	//temp
	//addEntity(Assemblages::getInstance().createPac(sf::Vector2f(300.0f, 200.0f), Right));
	//addEntity(Assemblages::getInstance().createBouncer(sf::Vector2f(300.0f, 300.0f)));

	//addEntity(Assemblages::getInstance().createDirectJimmy(sf::Vector2f(500.0f, 300.0f)));
	//addEntity(Assemblages::getInstance().createRoundJimmy(sf::Vector2f(500.0f, 300.0f)));

	//addEntity(Assemblages::getInstance().createAttackFly(sf::Vector2f(200.0f, 200.0f)));
	//addEntity(Assemblages::getInstance().createBombFly(sf::Vector2f(300.0f, 200.0f)));
	//addEntity(Assemblages::getInstance().createDaddyFly(sf::Vector2f(400.0f, 200.0f)));
	
	//addEntity(Assemblages::getInstance().createAttackFlySpawner(sf::Vector2f(200.0f, 300.0f)));
	//addEntity(Assemblages::getInstance().createBombFlySpawner(sf::Vector2f(400.0f, 300.0f)));

	//addEntity(Assemblages::getInstance().createRandomDashie(sf::Vector2f(800.0f, 300.0f)));
	//addEntity(Assemblages::getInstance().createDirectDashie(sf::Vector2f(800.0f, 300.0f)));

	//addEntity(Assemblages::getInstance().createSpinny(sf::Vector2f(800.0f, 300.0f)));
	//addEntity(Assemblages::getInstance().createBombSpinny(sf::Vector2f(800.0f, 300.0f)));

	//addEntity(Assemblages::getInstance().createWalker(sf::Vector2f(800.0f, 500.0f)));
	//addEntity(Assemblages::getInstance().createRoundShotWalker(sf::Vector2f(800.0f, 500.0f)));
}

Room::TileType Room::getTileType(int x, int y)
{
	return tileTypes[x][y];
}

void Room::addEntity(Entity entity)
{
	if(entity.hasComponent(Component::ComponentType::Health))
		enemies++;

	addEntityQueue.push_back(entity);
}

void Room::killEnemy(Entity& entity)
{
	entity.shouldDelete = true;
	addEntity(Assemblages::getInstance().createEnemyDeath(entity.position));
	addEntity(Assemblages::getInstance().createEnemyDeathStain(entity.position));

	if(entity.hasComponent(Component::ComponentType::Bouncer))
	{
		float speed = std::dynamic_pointer_cast<BouncerCom>(entity.getComponent(Component::ComponentType::Bouncer))->projectileSpeed;

		addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, sf::Vector2f(-1, -1) / (float)sqrt(2) * speed));
		addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, sf::Vector2f(1, -1) / (float)sqrt(2) * speed));
		addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, sf::Vector2f(1, 1) / (float)sqrt(2) * speed));
		addEntity(Assemblages::getInstance().createEnemyRegularProjectile(entity.position, sf::Vector2f(-1, 1) / (float)sqrt(2) * speed));
	}
	if(entity.hasComponent(Component::ComponentType::FlyMove))
	{
		std::shared_ptr<FlyMoveCom> moveCom = std::dynamic_pointer_cast<FlyMoveCom>(entity.getComponent(Component::ComponentType::FlyMove));

		if(moveCom->variation == FlyMoveCom::Variation::Bomb || moveCom->variation == FlyMoveCom::Variation::Daddy)
		{
			addEntity(Assemblages::getInstance().createEnemyBomb(entity.position));

			if(moveCom->variation == FlyMoveCom::Variation::Daddy)
			{
				float speed = 350.0f;
				int amount = 6;

				for(int i = 0; i < amount; i++)
				{
					float directionDeg = 2 * 3.1415f / amount * i;
					sf::Vector2f direction(std::cos(directionDeg), std::sin(directionDeg));

					addEntity(Assemblages::getInstance().createEnemyCollisionProjectile(entity.position, direction * speed));
				}
			}
		}
	}

	enemies--;
	if(enemies == 0)
	{
		float scale = Utilities::getInstance().getScale() * (float)tileSize;

		if(upOpen)
		{
			tileTypes[8][0] = TileType::floor;
			addEntity(Assemblages::getInstance().createBlockDestruction(sf::Vector2f(width * scale / 2.0f, scale / 2.0f)));
		}
		if(downOpen)
		{
			tileTypes[8][height - 1] = TileType::floor;
			addEntity(Assemblages::getInstance().createBlockDestruction(sf::Vector2f(width * scale / 2.0f, height * scale - scale / 2.0f)));
		}
		if(leftOpen)
		{
			tileTypes[0][6] = TileType::floor;
			addEntity(Assemblages::getInstance().createBlockDestruction(sf::Vector2f(scale / 2.0f, height * scale / 2.0f)));
		}
		if(rightOpen)
		{
			tileTypes[width - 1][6] = TileType::floor;
			addEntity(Assemblages::getInstance().createBlockDestruction(sf::Vector2f(width * scale - scale / 2.0f, height * scale / 2.0f)));
		}

		complete = true;
	}

	GameplayState::updatePlayerCoins(1);
}

std::vector<Entity>& Room::getEntities()
{
	return entities;
}

std::vector<Entity>& Room::getAddEntityQueue()
{
	return addEntityQueue;
}

void Room::drawForeground(sf::RenderWindow& window)
{
	window.draw(foregroundVertArr, &foregroundTex);
	
	if(!complete)
	{
		if(upOpen)
			window.draw(upBlock);
		if(downOpen)
			window.draw(downBlock);
		if(leftOpen)
			window.draw(leftBlock);
		if(rightOpen)
			window.draw(rightBlock);
	}
}

void Room::drawBackground(sf::RenderWindow& window)
{
	window.draw(backgroundVertArr, &backgroundTex);
}