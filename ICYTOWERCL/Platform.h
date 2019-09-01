#pragma once
#include <SFML\Graphics.hpp>
#include <Layer.h>

const int const_dist_between_platforms = 80;

#pragma once
class Platform
{
private:
	int floor;
	int length;
	int position;
	sf::Texture startTx;
	sf::Texture middleTx;
	sf::Texture endTx;
	sf::Text floorText;

	int generatePos();
	int generateLen();
public:
	sf::Sprite startSp;
	sf::Sprite middleSp;
	sf::Sprite endSp;

	Platform(int lvl);

	int getFloor();
	void render(sf::RenderWindow& window);
	void regenerate();
	void reset(int flr);
};