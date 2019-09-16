#pragma once
#include <SFML/Graphics.hpp>
#include <Layer.h>

namespace GameOver
{
	//extern bool gameOver;
	void init();

	bool isGameOver();
	void restartGame();
	void stopGame();
	void doLogic();
	void render(sf::RenderWindow& window, Layer& layer);
	void reset();
}
