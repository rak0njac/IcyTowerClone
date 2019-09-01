#pragma once
#include <SFML/Graphics.hpp>
#include <Font.h>
#include <Layer.h>

//rework as class in case of future multiplayer feature.
//no redundancy, so no consts.

namespace Score
{
	void changeScore(int i);
	void init();
	void doLogic();
	sf::Vector2i stop(); //
	bool isComboMode();

	void render(Layer& l, sf::RenderWindow& window);
	void reset();
}