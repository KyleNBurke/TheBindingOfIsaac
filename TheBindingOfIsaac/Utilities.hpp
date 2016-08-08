#pragma once

#include "stdafx.h"

class Utilities
{
public:
	static Utilities& getInstance();

	void initialize();

	float round(float value) const;
	float clamp(float value, float min, float max) const;
	float getHorIntersectionDepth(sf::FloatRect rectA, sf::FloatRect rectB) const;
	float getVertIntersectionDepth(sf::FloatRect rectA, sf::FloatRect rectB) const;

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