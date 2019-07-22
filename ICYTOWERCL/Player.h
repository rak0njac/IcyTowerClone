#ifndef PLAYER_H
#define PLAYER_H
#include <SFML\Graphics.hpp>

namespace Player
{
	void init();
	//void move(bool accelerate, float delta);
	void checkControls();
	void render(sf::RenderWindow& window);
	//void accelerate();
	//void slowdown(float slow);
}
#endif