#pragma once
#include <SFML/Graphics.hpp>
class Font
{
private:
	static sf::Font font;
public:
	static void init();
	static sf::Font& getFont();
};

