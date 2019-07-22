#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>

namespace Background
{
	extern sf::Sprite SBkg;
	extern sf::Sprite SWall;
	void init();
	void render(sf::RenderWindow& window, int layer);
}

#endif
