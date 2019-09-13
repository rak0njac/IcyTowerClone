#include <Game.h>

sf::RenderWindow window(sf::VideoMode(640, 480), "Icy Tower Clone // Written in C++ using SFML", sf::Style::Close);
sf::Event event;

sf::Music music;
Player player;
Layer layerBkg;
Layer layerWall(3);
PlatformLayer Game::layerPlatform(2);
Layer Game::layerHud(0);

bool debug;
bool resetting;

void Game::init()
{
	window.setFramerateLimit(100);
	window.setKeyRepeatEnabled(false);
	music.openFromFile("..\\Assets\\Sounds\\beat.ogg");
	music.setLoop(true);
	music.setVolume(70);
	music.play();

	Font::init();
	Background::init();
	Timer::init();
	Score::init();		 //rework if multiplayer
	GameOver::init();
	FadeEffect::init();

	debug = false;
	resetting = false;
}

void Game::logic()
{
	while (window.isOpen())
	{
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
					//if (!debug)
					//{
					//	debug = 1;
					//	window.setFramerateLimit(3);
					//}
					//else
					//{
					//	debug = 0;
					//	window.setFramerateLimit(100);
					//}
					if (GameOver::isGameOver())
					{
						resetting = true;
					}
				}
			}
		}

		if (resetting)
		{
			//window.clear();
			if (FadeEffect::fadeIn())
			{
				GameOver::restartGame();
				window.clear();
				layerBkg.render(window, Background::getSpBkg());
				layerPlatform.render(window); //layerplatform -- layerengine?
				player.render(window, layerPlatform);
				layerWall.render(window, Background::getSpWall());
				Score::render(layerHud, window);
			}
			layerHud.render(window, FadeEffect::getDrawable());
			window.display();
		}
		else
		{
			window.clear();

			layerBkg.move();
			layerBkg.render(window, Background::getSpBkg());

			if (!GameOver::isGameOver())
				Timer::render(layerHud, window);

			layerPlatform.move();
			layerPlatform.render(window); //layerplatform -- layerengine?

			player.doLogic(window, layerPlatform);
			player.render(window, layerPlatform);

			layerWall.move();
			layerWall.render(window, Background::getSpWall());

			if (!GameOver::isGameOver())
			{
				Timer::doLogic();
			}
			Score::doLogic();

			Score::render(layerHud, window);

			layerHud.render(window, Timer::SpClock);
			layerHud.render(window, Timer::SpClockHandle);

			GameOver::doLogic();
			GameOver::render(window, layerHud);

			window.display();
		}
	}
}

void Game::reset()
{
	layerBkg.reset();
	layerWall.reset();
	layerHud.reset();
	layerPlatform.reset();
	player.reset();
}