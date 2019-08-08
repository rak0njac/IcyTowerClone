#include <SFML/Graphics.hpp>
#include <Background.h>
#include <Camera.h>
#include <Player.h>
#include <Timer.h>
#include <Score.h>
#include <EyeCandy.h>
#include <iostream>
#include <Font.h>

//brzine 1,2,4,6,9,11

//Remove global variables?
//Make everything OOP?
//Define constants in headers?
//Add comments?


int main()
{
	bool debug = 0;

	sf::RenderWindow window(sf::VideoMode(640,480), "Icy Tower Clone // Written in C++ using SFML", sf::Style::Close);
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(false);

	Player p;

	Font::init();
	Background::init();
	Timer::init();
	Score::init();

	Layer layerBkg;
	Layer layerWall(3);
	PlatformLayer layerPlatform(2);
	Layer layerHud(0);

	while (window.isOpen())
	{
		//std::cout << p->cjSp.getPosition().y << "\n";
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (!debug)
					{
						debug = 1;
						window.setFramerateLimit(3);
					}
					else
					{
						debug = 0;
						window.setFramerateLimit(100);
					}
				}
			}
		}

		window.clear();

		layerBkg.move();
		layerBkg.render(window, Background::getSpBkg());

		layerPlatform.move();
		layerPlatform.render(window);

		p.doLogic(window, layerPlatform);
		p.render(window, layerPlatform);

		layerWall.move();
		layerWall.render(window, Background::getSpWall());

		Timer::doLogic();
		Score::doLogic();

		layerHud.render(window, Timer::SpClock);
		layerHud.render(window, Timer::SpClockHandle);
		//layerHud.render(window, Score::spComboMeter);
		//layerHud.render(window, Score::spComboMeterBar);
		//layerHud.render(window, Score::star);
		//layerHud.render(window, Score::textComboFloors);
		//layerHud.render(window, Score::textConstFloors);
		//layerHud.render(window, Score::textScore);

		Score::render(layerHud, window);

		window.display();
	}
	return 0;
}