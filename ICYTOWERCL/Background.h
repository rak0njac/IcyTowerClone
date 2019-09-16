#pragma once
#include <SFML/Graphics.hpp>
#include <Game.h>

namespace Background
{
	enum Sprites
	{
		Background,
		Wall
	};

	void init();
	void render(sf::RenderWindow& window, int sprite);
	void reset();
}