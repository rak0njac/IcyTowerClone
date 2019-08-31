#pragma once
#include <SFML/Graphics.hpp>

class Background
{
private:
	static sf::Texture txBkg;
	static sf::Texture txWall;
	static sf::Sprite spBkg;
	static sf::Sprite spWall;
public:
	static sf::Sprite& getSpBkg();
	static sf::Sprite& getSpWall();
	static void init()
};