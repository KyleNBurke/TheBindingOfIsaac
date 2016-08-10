#include "stdafx.h"
#include "ProjectileSystem.hpp"
#include "Floor.hpp"
#include "HealthCom.hpp"
#include "AnimationStateDynamic.hpp"
//#include "Assemblages.hpp"

ProjectileSystem::ProjectileSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void ProjectileSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Projectile))
	{
		std::shared_ptr<ProjectileCom> projCom = std::dynamic_pointer_cast<ProjectileCom>(entity.getComponent(Component::ComponentType::Projectile));
		std::shared_ptr<LifetimeCom> lifetimeCom = std::dynamic_pointer_cast<LifetimeCom>(entity.getComponent(Component::ComponentType::Lifetime));
		std::shared_ptr<VelocityCom> velCom = std::dynamic_pointer_cast<VelocityCom>(entity.getComponent(Component::ComponentType::Velocity));
		std::shared_ptr<AnimationCom> animCom = std::dynamic_pointer_cast<AnimationCom>(entity.getComponent(Component::ComponentType::Animation));
		std::shared_ptr<AnimationStateDynamic> state = std::dynamic_pointer_cast<AnimationStateDynamic>(animCom->states[1]);

		lifetimeCom->elapsedTime += deltaTime.asSeconds();

		if(projCom->alive)
		{
			if(lifetimeCom->elapsedTime >= lifetimeCom->lifetime)
			{
				removeProjectile(entity, projCom, animCom, velCom, lifetimeCom);
				return;
			}

			if(detectTileCollisions(entity))
			{
				removeProjectile(entity, projCom, animCom, velCom, lifetimeCom);
				return;
			}

			if(detectEntityCollisions(entity, projCom))
			{
				entity.shouldDelete = true;
			}
		}
		else
		{
			if(lifetimeCom->elapsedTime >= state->frameCount * state->frameTime)
				entity.shouldDelete = true;
		}
	}
}

bool ProjectileSystem::detectTileCollisions(Entity& entity)
{
	int scale = Room::tileSize * Utilities::getInstance().getScale();
	sf::FloatRect entityBounds = entity.getBounds();

	if(entityBounds.left < 0.0f ||
		entityBounds.top < 0.0f ||
		entityBounds.left + entityBounds.width > Room::width * scale ||
		entityBounds.top + entityBounds.height > Room::height * scale)
	{
		return true;
	}
	

	int left = (int)(std::floorf(entityBounds.left / scale));
	int right = (int)(std::ceilf((entityBounds.left + entityBounds.width) / scale)) - 1;
	int top = (int)(std::floorf(entityBounds.top / scale));
	int bottom = (int)(std::ceilf((entityBounds.top + entityBounds.height) / scale)) - 1;

	for(int x = left; x <= right; x++)
		for(int y = top; y <= bottom; y++)
			if(Floor::getCurrentRoom().getTileType(x, y) == Room::TileType::wall)
				return true;

	return false;
}

bool ProjectileSystem::detectEntityCollisions(Entity& entity, std::shared_ptr<ProjectileCom> projCom)
{
	if(projCom->projectileType == ProjectileCom::ProjectileType::Player)
	{
		for(std::vector<Entity>::iterator it = Floor::getCurrentRoom().entities.begin(); it != Floor::getCurrentRoom().entities.end(); ++it)
		{
			bool intersects = entity.getBounds().intersects(it->sprite.getGlobalBounds());
			if(it->hasComponent(Component::ComponentType::Health) && intersects)
			{
				applyDamage(*it, 1);
				return true;
			}
		}
	}
	else
	{
		if(entity.getBounds().intersects(Floor::player.sprite.getGlobalBounds()))
		{
			applyDamage(Floor::player, 1);
			return true;
		}
	}

	return false;
}

void ProjectileSystem::applyDamage(Entity& entity, int damage)
{
	std::shared_ptr<HealthCom> healthCom = std::dynamic_pointer_cast<HealthCom>(entity.getComponent(Component::ComponentType::Health));
	healthCom->health -= damage;

	if(healthCom->health <= 0)
		entity.shouldDelete = true;
}

void ProjectileSystem::removeProjectile(Entity& entity,
	std::shared_ptr<ProjectileCom> projCom,
	std::shared_ptr<AnimationCom> animCom,
	std::shared_ptr<VelocityCom> velCom,
	std::shared_ptr<LifetimeCom> lifetimeCom)
{
	projCom->alive = false;

	animCom->currentState = 1;

	std::shared_ptr<AnimationStateDynamic> animState = std::dynamic_pointer_cast<AnimationStateDynamic>(animCom->states[1]);
	entity.sprite.move(sf::Vector2f((float)animState->offsetX, (float)animState->offsetY) * (float)Utilities::getInstance().getScale());

	velCom->velocity.x = 0.0f;
	velCom->velocity.y = 0.0f;

	lifetimeCom->elapsedTime = 0.0f;
}