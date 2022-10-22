#pragma once
#include <Layer.h>
#include <SFML/Graphics.hpp>
#include <DefaultFont.h>
#include <random>
#include <FloorTypes.h>
#include <iostream>
#include <Consts.h>

class Platform
{
private:
	int floor;
	int length;
	int position;
	static sf::Image imgPlatform;
	static sf::Texture txPlatform;
	sf::Text textFloor;
	std::vector<sf::IntRect> vect;

	int generatePos();
	int generateLen();
public:
	sf::Sprite spPlatform;
	float startPos;
	float endPos;
	Platform(int lvl);

	int getFloor();
	static void init();
	void render(sf::RenderWindow& window);
	void regenerate();
	void reset(int flr);
};