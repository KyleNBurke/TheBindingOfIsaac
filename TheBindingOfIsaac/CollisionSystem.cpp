#include "stdafx.h"
#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() {}

void CollisionSystem::update(std::vector<Entity>& entities) {
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<Component> component = it->getComponent(Component::ComponentType::Velocity);
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

			int tileSize = Room::tileSize;

			if(it->getPosition().x < tileSize * Utilities::getInstance().getScale()) {
				it->getPosition().x = tileSize * Utilities::getInstance().getScale();
				velocityCom->getVelocity().x = 0.0f;
			}
			if(it->getPosition().y < tileSize * Utilities::getInstance().getScale()) {
				it->getPosition().y = tileSize * Utilities::getInstance().getScale();
				velocityCom->getVelocity().y = 0.0f;
			}
			if(it->getPosition().x + it->getSprite().getGlobalBounds().width > (Room::width + 1) * tileSize * Utilities::getInstance().getScale()) {
				it->getPosition().x = (Room::width + 1) * tileSize * Utilities::getInstance().getScale() - it->getSprite().getGlobalBounds().width;
				velocityCom->getVelocity().x = 0.0f;
			}
			if(it->getPosition().y + it->getSprite().getGlobalBounds().height > (Room::height + 1) * tileSize * Utilities::getInstance().getScale()) {
				it->getPosition().y = (Room::height + 1) * tileSize * Utilities::getInstance().getScale() - it->getSprite().getGlobalBounds().height;
				velocityCom->getVelocity().y = 0.0f;
			}

			bool hasPitCollision = it->hasComponent(Component::ComponentType::PitCollision);
			bool hasWallCollision = it->hasComponent(Component::ComponentType::WallCollision);

			if(hasPitCollision || hasWallCollision)
			{
				it->getPosition().x = Utilities::getInstance().round(it->getPosition().x);
				resolveCollisions(Direction::Horizontal, *it, *velocityCom, hasPitCollision, hasWallCollision);
				it->getPosition().y = Utilities::getInstance().round(it->getPosition().y);
				resolveCollisions(Direction::Vertical, *it, *velocityCom, hasPitCollision, hasWallCollision);
			}
		}
	}
}

void CollisionSystem::resolveCollisions(Direction direction, Entity& entity, VelocityCom& velocityCom, bool hasPitCollision, bool hasWallCollision)
{
	sf::FloatRect entityBounds = entity.getEntityBounds();
	int scale = Room::tileSize * Utilities::getInstance().getScale();

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	for(int x = left; x <= right; x++)
	{
		for(int y = top; y <= bottom; y++)
		{
			Room::TileType tileType = Map::getCurrentRoom().getTileType(x, y);

			if((hasPitCollision && tileType == Room::TileType::pit) || (hasWallCollision && tileType == Room::TileType::wall))
			{
				sf::IntRect tile(x * scale, y * scale, scale, scale);

				float depth;
				if(direction == Direction::Horizontal)
				{
					depth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)entity.getEntityBounds(), tile);

					if(depth != 0.0f)
					{
						entity.getPosition().x += depth;
						velocityCom.getVelocity().x = 0.0f;
						entityBounds = entity.getEntityBounds();
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)entity.getEntityBounds(), tile);

					if(depth != 0.0f)
					{
						entity.getPosition().y += depth;
						velocityCom.getVelocity().y = 0.0f;
						entityBounds = entity.getEntityBounds();
					}
				}
			}
		}
	}
}