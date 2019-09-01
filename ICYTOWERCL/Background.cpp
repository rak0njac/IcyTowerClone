#include <Background.h>

sf::Texture txBkg;
sf::Texture txWall;
sf::Sprite spBkg;
sf::Sprite spWall;

void Background::init()
{
	txBkg.loadFromFile("..\\Assets\\Bkg2.png");
	spBkg.setTexture(txBkg);
	spBkg.setOrigin(253, 0);
	spBkg.setPosition(320, -62);
	spBkg.scale(1.02f, 1);					//Corrects a small asset mistake where a few golden pixels can be seen

	txWall.loadFromFile("..\\Assets\\Wallz3.png");
	spWall.setTexture(txWall);
	//SWall.setOrigin(320, 0);
	spWall.setPosition(0, -124);
}

const sf::Sprite& Background::getSpBkg()
{
	return spBkg;
}

const sf::Sprite& Background::getSpWall()
{
	return spWall;
}

void Background::reset()
{
	spBkg.setPosition(320, -62);
	spWall.setPosition(0, -124);
}