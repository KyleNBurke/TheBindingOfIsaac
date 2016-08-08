#pragma once

#include "stdafx.h"
#include "State.hpp"
#include "StatsState.hpp"
#include "Floor.hpp"
#include "HUD.hpp"

#include "Assemblages.hpp"
#include "RenderSystem.hpp"
#include "InputSystem.hpp"
#include "PhysicsSystem.hpp"
#include "ShotSystem.hpp"
#include "ProjectileSystem.hpp"
#include "TransitionSystem.hpp"
#include "AnimationSystem.hpp"
#include "MovementSystem.hpp"

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
	Floor floor;

	std::vector<std::unique_ptr<System>> systems;
	TransitionSystem transitionSystem;
	RenderSystem renderSystem;
};