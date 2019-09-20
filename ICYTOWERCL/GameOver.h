#pragma once
#include <SFML/Graphics.hpp>

namespace GameOver
{
	void init();

	bool isGameOver();
	void restartGame();
	void stopGame();
	void logic();
	void render(sf::RenderWindow& window);
	void reset();
}
