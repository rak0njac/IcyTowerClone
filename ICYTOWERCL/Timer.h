#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Layer.h>
#include <DefaultFont.h>
#include <Game.h>

const int const_timer_start_pos_x = 42;
const int const_timer_start_pos_y = 56;
const int const_timer_start_bound = 20;

namespace Timer {
	static sf::Clock clock;
	static sf::Time time;

	bool getStarted();
	void setStarted(bool start);

	void init();
	void logic();
	void reset();
	void render(sf::RenderWindow& window, int sprite);

	enum Sprites
	{
		Clock,
		HurryUpText
	};
}