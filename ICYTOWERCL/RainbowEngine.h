#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class RainbowEngine : public sf::Text
{
private:
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

public:
	RainbowEngine(sf::Text& text);
	static sf::Color changeColor(const sf::Color& color, const int col);
	void textMagic(sf::RenderWindow& window);
	void resetText(sf::Text& text);
};