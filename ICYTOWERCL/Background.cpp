#include <Background.h>

sf::Texture Background::txBkg;
sf::Texture Background::txWall;
sf::Sprite Background::spBkg;
sf::Sprite Background::spWall;

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

sf::Sprite& Background::getSpBkg()
{
	return spBkg;
}

sf::Sprite& Background::getSpWall()
{
	return spWall;
}