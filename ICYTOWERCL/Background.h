#pragma once
#include <SFML/Graphics.hpp>

namespace Background
{
	namespace Sprite
	{
		extern sf::Sprite spBkg;
		extern sf::Sprite spWall;
	}

	void init();
	void reset();
}