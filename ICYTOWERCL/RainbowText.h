#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Layer.h>
#include <DefaultFont.h>
#include <iostream>

class RainbowText : public sf::Text	//for proper OOP it would be better to inherit from Font, Drawable and Transformable, but I think it's overkill
{
private:
	bool initialized;
	bool colorsInitialized;
	bool charsInitialized;
	sf::Text comp;	//used in textMagic() to compare old and new strings
	int numOfColors;
	int numOfChars;
	std::vector<sf::Text> chars;
	std::vector<sf::Color> colors;
	Layer* layer;

	//see explanation for these in textMagic()
	bool magicSkipper;
	int magicX;
	int magicY;
public:
	using Text::Text;
	static sf::Color changeColor(const sf::Color& color, const int col);
	void init();
	void setLayer(Layer& _layer);
	void logic();
	void render(sf::RenderWindow& window);
};