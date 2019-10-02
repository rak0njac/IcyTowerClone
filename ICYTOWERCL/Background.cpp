#include <Background.h>

sf::Texture txBkg;
sf::Texture txWall;
sf::Sprite spBkg;
sf::Sprite spWall;

void Background::init()
{
	txBkg.loadFromFile("..\\Assets\\Bkg2.png");
	spBkg.setTexture(txBkg);
	spBkg.setOrigin(txBkg.getSize().x / 2, 64);
	spBkg.setPosition(320, 0);

	txWall.loadFromFile("..\\Assets\\Wallz3.png");
	spWall.setTexture(txWall);
	spWall.setOrigin(0, 128);

	//each line of bricks in bkg is 32px high and in wall 64px
}

void Background::render(sf::RenderWindow& window, int sprite)
{
	if (sprite == Background::Sprites::Background)
		Game::Layers::Background.render(window, spBkg);
	else if (sprite == Background::Sprites::Wall)
		Game::Layers::Wall.render(window, spWall);
}

void Background::reset()
{
	spBkg.setPosition(320, 0);
	spWall.setPosition(0, 0); //CHECK
}