#pragma once
#include <SFML/Graphics.hpp>

namespace FadeEffect
{
	void init();
	void fade(int alpha);
	bool fadeIn();
	bool fadeOut();

	sf::Drawable& getDrawable();
}