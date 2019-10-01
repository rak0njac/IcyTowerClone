#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Layer.h>
#include <DefaultFont.h>
#include <Game.h>

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