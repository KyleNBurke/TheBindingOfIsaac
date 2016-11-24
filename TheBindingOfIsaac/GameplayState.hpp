#pragma once

#include "stdafx.h"
#include "State.hpp"
#include "StatsState.hpp"
#include "Floor.hpp"
#include "HUD.hpp"
#include "RenderSystem.hpp"
#include "TransitionSystem.hpp"


class GameplayState : public State
{
public:
	GameplayState(StatsState& statsState, sf::RenderWindow& window, const sf::Time& deltaTime);

	void initialize();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	static void givePlayerCoins(int amount);

private:
	StatsState& statsState;
	HUD hud;
	Floor floor;

	std::vector<std::unique_ptr<System>> systems;
	TransitionSystem transitionSystem;
	RenderSystem renderSystem;

	static int playerCoins;
};