#pragma once
#include <SFML/Graphics.hpp>

class DefaultFont
{
private:
	static sf::Font font;
public:
	static void init();
	static const sf::Font& getFont();
};

