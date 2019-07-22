#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML\Graphics.hpp>
#include <Layer.h>

class Platform
{
private:
	int level;
	int length;
	int position;
	sf::Texture startTx;
	sf::Texture middleTx;
	sf::Texture endTx;

	int generatePos();
	int generateLen();
	

public:
	int floor;
	const int yDistance = 80;
	sf::Sprite startSp;
	sf::Sprite middleSp;
	sf::Sprite endSp;

	Platform(int x);
	~Platform();

	void render(sf::RenderWindow& window);
	void regenerate();
};

#endif
