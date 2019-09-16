#include <Background.h>

sf::Texture txBkg;
sf::Texture txWall;
sf::Sprite Background::Sprite::spBkg;
sf::Sprite Background::Sprite::spWall;

using namespace Background::Sprite;

void Background::init()
{
	txBkg.loadFromFile("..\\Assets\\Bkg2.png");
	spBkg.setTexture(txBkg);
	spBkg.setOrigin(txBkg.getSize().x / 2, 62);
	spBkg.setPosition(320, 0);

	txWall.loadFromFile("..\\Assets\\Wallz3.png");
	spWall.setTexture(txWall);
	spWall.setOrigin(0, 124);

	//each line of bricks in bkg is 31px high and in wall 62px
}

void Background::reset()
{
	spBkg.setPosition(320, 0);
	spWall.setPosition(0, 0); //CHECK
}