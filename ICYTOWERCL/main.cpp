#include <SFML/Graphics.hpp>
#include <Background.h>
#include <Camera.h>
#include <Player.h>
#include <PlatformLayer.h>
#include <iostream>

//brzine 1,2,4,6,9,11

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Icy Tower Clone // Written in C++ using SFML");
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(false);
	Background::init();
	Player::init();
	Layer layerBkg(Camera::startStep);
	Layer layerWall(Camera::startStep, 3);
	PlatformLayer layerPlatform(Camera::startStep, 2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					Camera::camSpeed++;
				}
			}
		}

		Player::checkControls();
		window.clear();

		layerBkg.move(Camera::camSpeedFactor, Camera::camSpeed, Camera::startStep);
		layerBkg.render(window, Background::SBkg);

		layerPlatform.move(Camera::camSpeedFactor, Camera::camSpeed);
		layerPlatform.render(window);

		Player::render(window);

		layerWall.move(Camera::camSpeedFactor, Camera::camSpeed, Camera::startStep);
		layerWall.render(window, Background::SWall);

		window.display();
	}
	return 0;
}