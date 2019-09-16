#pragma once
#include <SFML/Graphics.hpp>
#include <Layer.h>

namespace GameOver
{
	void init();

	bool isGameOver();
	void restartGame();
	void stopGame();
	void logic();
	void reset();
}
