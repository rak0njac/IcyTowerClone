#pragma once
#include <SFML/Graphics.hpp>
#include <DefaultFont.h>
#include <Layer.h>
#include <string.h>
#include <iostream>
#include <RainbowText.h>
#include <GameOver.h>
#include <EyeCandyEngine.h>
#include <Game.h>

//rework as class in case of future multiplayer feature.
//no redundancy, so no consts.



namespace Score
{
	void changeScore(int i);
	void init();
	void logic();
	sf::Vector2i stop(); //returns the values needed at GameOver.cpp
	bool isComboMode();

	void render(sf::RenderWindow& window);
	void reset();
}