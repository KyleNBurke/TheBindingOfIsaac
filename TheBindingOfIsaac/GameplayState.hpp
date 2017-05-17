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
	GameplayState(StatsState& statsState);

	void initialize();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	void reset();

	static void updatePlayerBombs(int amount);
	static int getPlayerBombs();
	static void updatePlayerCoins(int amount);
	static int getPlayerCoins();

	StatsState& getStatsState() const;

private:
	StatsState& statsState;
	HUD hud;
	Floor floor;

	std::vector<std::unique_ptr<System>> systems;
	TransitionSystem transitionSystem;
	RenderSystem renderSystem;

	int currentFloor;
	static int playerBombs;
	static int playerCoins;
};