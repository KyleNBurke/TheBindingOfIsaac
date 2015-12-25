#pragma once

#include "stdafx.h"
#include "State.hpp"
#include "StatsState.hpp"
#include "Map.hpp"
#include "HUD.hpp"
#include "Player.hpp"

#include "Assemblages.hpp"
#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "CollisionSystem.hpp"

class GameplayState : public State
{
public:
	GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime);

	void initialize();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

private:
	StatsState& statsState;
	HUD hud;
	Map map;
	Player player;

	std::vector<Entity> entities;
	RenderSystem renderSystem;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	CollisionSystem collisionSystem;
};