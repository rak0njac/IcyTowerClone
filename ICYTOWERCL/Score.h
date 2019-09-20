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

const sf::Color const_color_outline(1, 26, 51, 255);
const int const_text_size_small = 20;
const int const_text_size_medium = 30;
const int const_text_size_large = 140;
const int const_text_outline_small = 1;
const int const_text_outline_medium = 3;
const int const_text_outline_large = 7;

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