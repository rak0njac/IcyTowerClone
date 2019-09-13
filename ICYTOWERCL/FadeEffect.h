#pragma once
#include <SFML/Graphics.hpp>

namespace FadeEffect
{
	void init();
	bool fadeIn();
	bool fadeOut();

	sf::Drawable& getDrawable();
}