#pragma once
#include <SFML/Graphics.hpp>

namespace Background
{
	const sf::Sprite& getSpBkg();
	const sf::Sprite& getSpWall();
	void init();
	void reset();
}