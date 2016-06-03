#include "stdafx.h"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void PhysicsSystem::update(std::vector<Entity>& entities)
{
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::AccelDecel))
		{
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(it->getComponent(Component::ComponentType::Velocity));
			std::shared_ptr<AccelDecelCom> accelDecelCom = std::dynamic_pointer_cast<AccelDecelCom>(it->getComponent(Component::ComponentType::AccelDecel));

			velocityCom->velocity.x += velocityCom->direction.x * accelDecelCom->acceleration;
			velocityCom->velocity.y += velocityCom->direction.y * accelDecelCom->acceleration;

			velocityCom->velocity *= accelDecelCom->deceleration;
		}

		if(it->hasComponent(Component::ComponentType::Velocity))
		{
			int tileSize = Room::tileSize * Utilities::getInstance().getScale();
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(it->getComponent(Component::ComponentType::Velocity));
			bool hasPitCollision = it->hasComponent(Component::ComponentType::PitCollision);
			bool hasWallCollision = it->hasComponent(Component::ComponentType::WallCollision);
			
			it->position.x += Utilities::getInstance().round(velocityCom->velocity.x * deltaTime.asSeconds());

			if(it->position.x < tileSize) {
				it->position.x = (float)tileSize;
				velocityCom->velocity.x = 0.0f;
			}
			if(it->position.x + getEntityBounds(*it).width >(Room::width + 1) * tileSize) {
				it->position.x = (Room::width + 1) * tileSize - getEntityBounds(*it).width;
				velocityCom->velocity.x = 0.0f;
			}

			if(hasPitCollision || hasWallCollision) {
				resolveCollisions(Direction::Horizontal, *it, hasPitCollision, hasWallCollision);
			}

			it->position.y += Utilities::getInstance().round(velocityCom->velocity.y * deltaTime.asSeconds());

			if(it->position.y < tileSize) {
				it->position.y = (float)tileSize;
				velocityCom->velocity.y = 0.0f;
			}
			if(it->position.y + getEntityBounds(*it).width >(Room::width + 1) * tileSize) {
				it->position.y = (Room::width + 1) * tileSize - getEntityBounds(*it).width;
				velocityCom->velocity.y = 0.0f;
			}

			if(hasPitCollision || hasWallCollision) {
				resolveCollisions(Direction::Vertical, *it, hasPitCollision, hasWallCollision);
			}

			it->sprite.setPosition(it->position);
		}
	}
}

void PhysicsSystem::resolveCollisions(Direction direction, Entity& entity, bool hasPitCollision, bool hasWallCollision)
{
	sf::FloatRect entityBounds = getEntityBounds(entity);
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
					depth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.position.x += depth;
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.x = 0.0f;
						entityBounds = getEntityBounds(entity);
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						entity.position.y += depth;
						std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity))->velocity.x = 0.0f;
						entityBounds = getEntityBounds(entity);
					}
				}
			}
		}
	}
}

sf::FloatRect PhysicsSystem::getEntityBounds(const Entity& entity)
{
	return sf::FloatRect(entity.position.x, entity.position.y, entity.sprite.getGlobalBounds().width, entity.sprite.getGlobalBounds().height);
}