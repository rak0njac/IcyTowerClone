#include <Background.h>
#include <Camera.h>
#include <iostream>

sf::Texture		TBkg;
sf::Sprite		Background::SBkg;
sf::Texture		TWall;
sf::Sprite		Background::SWall;


void Background::init()
{
	TBkg.loadFromFile("..\\Assets\\Bkg2.png");
	SBkg.setTexture(TBkg);
	SBkg.setOrigin(253, 0);
	SBkg.setPosition(320, -62);
	SBkg.scale(1.02f, 1);					//Corrects a small asset mistake where a few golden pixels can be seen

	TWall.loadFromFile("..\\Assets\\Wallz3.png");
	SWall.setTexture(TWall);
	//SWall.setOrigin(320, 0);
	SWall.setPosition(0, -124);
}