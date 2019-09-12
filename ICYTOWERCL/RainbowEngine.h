#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Layer.h>

class RainbowEngine : public sf::Text
{
private:
	bool reInitialized = false;
	bool colorsInitialized;
	bool charsInitialized;
	sf::Text comp;
	int numOfColors;
	int numOfChars;
	sf::Text* text;
	std::vector<sf::Text> chars;
	std::vector<sf::Color> colors;
	int skipper;
	int x;
	int y;

	void init();

public:
	RainbowEngine(sf::Text text);
	//RainbowEngine(){}
	//using namespace sf;
	using Text::Text;
	static sf::Color changeColor(const sf::Color& color, const int col);
	void textMagic(sf::RenderWindow& window, Layer& layer);
	void resetText(sf::Text& text);
};