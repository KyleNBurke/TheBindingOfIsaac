#pragma once

#include "stdafx.h"

class Utilities
{
public:
	static Utilities& getInstance();

	void initialize();

	float round(float value) const;
	float clamp(float value, float min, float max) const;
	float getHorIntersectionDepth(sf::IntRect rectA, sf::IntRect rectB) const;
	float getVertIntersectionDepth(sf::IntRect rectA, sf::IntRect rectB) const;

	int getScale() const;
	sf::Font& getFont();

private:
	Utilities();
	Utilities(const Utilities&);
	void operator=(const Utilities&);

	const int scale;
	sf::Font font;
};

enum Direction {
	Up,
	Down,
	Left,
	Right
};