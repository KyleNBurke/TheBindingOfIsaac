#include "stdafx.h"
#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void CollisionSystem::update(std::vector<Entity>& entities) {
	for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if(it->hasComponent(Component::ComponentType::Velocity))
		{
			std::shared_ptr<Component> component = it->getComponent(Component::ComponentType::Velocity);
			std::shared_ptr<VelocityCom> velocityCom = std::dynamic_pointer_cast<VelocityCom>(component);

			sf::Vector2f& position = it->getPosition();
			sf::Vector2f& velocity = velocityCom->getVelocity();
			int tileSize = Room::tileSize * Utilities::getInstance().getScale();
			sf::FloatRect bounds = it->getSprite().getGlobalBounds();
			bool hasPitCollision = it->hasComponent(Component::ComponentType::PitCollision);
			bool hasWallCollision = it->hasComponent(Component::ComponentType::WallCollision);

			position.x += Utilities::getInstance().round(velocity.x * deltaTime.asSeconds());

			if(position.x < tileSize) {
				position.x = (float)tileSize;
				velocity.x = 0.0f;
			}

			if(position.x + bounds.width > (Room::width + 1) * tileSize) {
				position.x = (Room::width + 1) * tileSize - bounds.width;
				velocity.x = 0.0f;
			}

			if(hasPitCollision || hasWallCollision) {
				resolveCollisions(Direction::Horizontal, *it, position, velocity, hasPitCollision, hasWallCollision);
			}

			position.y += Utilities::getInstance().round(velocity.y * deltaTime.asSeconds());

			if(position.y < tileSize) {
				position.y = (float)tileSize;
				velocity.y = 0.0f;
			}

			if(position.y + bounds.height > (Room::height + 1) * tileSize) {
				position.y = (Room::height + 1) * tileSize - bounds.height;
				velocity.y = 0.0f;
			}

			if(hasPitCollision || hasWallCollision) {
				resolveCollisions(Direction::Vertical, *it, position, velocity, hasPitCollision, hasWallCollision);
			}

			/*if(it->getPosition().x < tileSize * Utilities::getInstance().getScale()) {
				position.x = (float)tileSize * Utilities::getInstance().getScale();
				velocityCom->getVelocity().x = 0.0f;
			}
			if(it->getPosition().y < tileSize * Utilities::getInstance().getScale()) {
				position.y = (float)tileSize * Utilities::getInstance().getScale();
				velocityCom->getVelocity().y = 0.0f;
			}
			if(it->getPosition().x + it->getSprite().getGlobalBounds().width > (Room::width + 1) * tileSize * Utilities::getInstance().getScale()) {
				position.x = (Room::width + 1) * tileSize * Utilities::getInstance().getScale() - it->getSprite().getGlobalBounds().width;
				velocityCom->getVelocity().x = 0.0f;
			}
			if(it->getPosition().y + it->getSprite().getGlobalBounds().height > (Room::height + 1) * tileSize * Utilities::getInstance().getScale()) {
				position.y = (Room::height + 1) * tileSize * Utilities::getInstance().getScale() - it->getSprite().getGlobalBounds().height;
				velocityCom->getVelocity().y = 0.0f;
			}

			bool hasPitCollision = it->hasComponent(Component::ComponentType::PitCollision);
			bool hasWallCollision = it->hasComponent(Component::ComponentType::WallCollision);

			if(hasPitCollision || hasWallCollision)
			{
				//position.x = Utilities::getInstance().round(velocityCom->getVelocity().x * );
				resolveCollisions(Direction::Horizontal, *it, position, *velocityCom, hasPitCollision, hasWallCollision);
				//position.y = Utilities::getInstance().round(position.y);
				resolveCollisions(Direction::Vertical, *it, position, *velocityCom, hasPitCollision, hasWallCollision);
			}*/

			it->getSprite().setPosition(position);
		}
	}
}

void CollisionSystem::resolveCollisions(Direction direction, Entity& entity, sf::Vector2f& position, sf::Vector2f& velocity, bool hasPitCollision, bool hasWallCollision)
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
					depth = Utilities::getInstance().getHorIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						position.x += depth;
						velocity.x = 0.0f;
						entityBounds = entity.getEntityBounds();
					}
				}
				else
				{
					depth = Utilities::getInstance().getVertIntersectionDepth((sf::IntRect)entityBounds, tile);

					if(depth != 0.0f)
					{
						position.y += depth;
						velocity.y = 0.0f;
						entityBounds = entity.getEntityBounds();
					}
				}
			}
		}
	}
}