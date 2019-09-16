#include <Game.h>
#include <RainbowEngine.h>

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

int gameState;

void Game::init()
{
	setState(Game::State::Loading);
}

void Game::setState(int state)
{
	gameState = state;
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
						GameOver::restartGame();
					}
				}
			}
		}

		if (gameState == State::InGame)
		{
			window.clear();

			layerBkg.move();
			layerBkg.render(window, Background::getSpBkg());

			//if (!GameOver::isGameOver())
			Timer::render(layerHud, window);	//hurryup

			layerPlatform.move();
			layerPlatform.render(window); //layerplatform -- layerengine?

			player.doLogic(window, layerPlatform);
			player.render(window, layerPlatform);

			layerWall.move();
			layerWall.render(window, Background::getSpWall());

			//if (!GameOver::isGameOver())
			//{
			Timer::doLogic();
			//}
			Score::doLogic();

			Score::render(layerHud, window);

			layerHud.render(window, Timer::SpClock);
			layerHud.render(window, Timer::SpClockHandle);

			//GameOver::doLogic();
			//GameOver::render(window, layerHud);

			window.display();
		}
		else if (gameState ==  State::GameOver)
		{ 
			window.clear();
			layerBkg.render(window, Background::getSpBkg());
			layerPlatform.render(window); //layerplatform -- layerengine?
			player.doLogic(window, layerPlatform);
			player.render(window, layerPlatform);
			layerWall.render(window, Background::getSpWall());
			Score::doLogic();
			Score::render(layerHud, window);

			layerHud.render(window, Timer::SpClock);
			layerHud.render(window, Timer::SpClockHandle);
			GameOver::doLogic();
			GameOver::render(window, layerHud);

			window.display();

		}
		else if (gameState == State::Resetting)
		{
			static int i = 0;
			static int phase = 0;
			if (phase == 0)
			{
				music.stop();
				phase++;
			}
			else if (phase == 1)
			{
				if (i < 51)
				{
					window.clear();
					layerBkg.render(window, Background::getSpBkg());
					layerPlatform.render(window); //layerplatform -- layerengine?
					player.render(window, layerPlatform);
					layerWall.render(window, Background::getSpWall());
					Score::render(layerHud, window);

					layerHud.render(window, Timer::SpClock);
					layerHud.render(window, Timer::SpClockHandle);
					GameOver::render(window, layerHud);
					FadeEffect::fade(i * 5);
					layerHud.render(window, FadeEffect::getDrawable());
					window.display();

					i++;
				}
				else phase++;
			}
			else if (phase == 2)
			{
				Background::reset();
				Score::reset();
				Timer::reset();
				Game::reset();
				GameOver::reset();

				music.stop();
				window.clear();

				layerBkg.render(window, Background::getSpBkg());

				layerPlatform.render(window); //layerplatform -- layerengine?

				player.doLogic(window, layerPlatform);
				player.render(window, layerPlatform);
				layerWall.render(window, Background::getSpWall());

				Timer::doLogic();
				Score::doLogic();

				Score::render(layerHud, window);

				layerHud.render(window, Timer::SpClock);
				layerHud.render(window, Timer::SpClockHandle);
				//window.display();
				phase++;
			}
			else if (phase == 3)
			{
				if (i > 0)
				{
					window.clear();
					layerBkg.render(window, Background::getSpBkg());
					layerPlatform.render(window); //layerplatform -- layerengine?
					player.render(window, layerPlatform);
					layerWall.render(window, Background::getSpWall());
					Score::render(layerHud, window);

					layerHud.render(window, Timer::SpClock);
					layerHud.render(window, Timer::SpClockHandle);
					GameOver::render(window, layerHud);
					FadeEffect::fade(i * 5);
					layerHud.render(window, FadeEffect::getDrawable());
					window.display();

					i--;
				}
				else phase++;
			}
			else if (phase == 4)
			{
				music.play();
				setState(Game::State::InGame);
				phase = 0;
				//done!
			}
		}
		else if (gameState == Game::State::Loading)
		{
			window.setFramerateLimit(100);
			window.setKeyRepeatEnabled(false);

			music.openFromFile("..\\Assets\\Sounds\\beat.ogg");
			music.setLoop(true);
			music.setVolume(70);

			Font::init();
			RainbowEngine re("LOADING...", Font::getFont(), 140);
			re.setOrigin(re.getLocalBounds().width * 0.5, re.getLocalBounds().height * 0.5);
			re.setPosition(320, 240);
			re.textMagic(window, layerHud);

			window.display();

			Background::init();
			Timer::init();
			Score::init();	
			GameOver::init();
			FadeEffect::init();
			player.init();
			music.play();

			window.clear();
			window.display();

			setState(Game::State::InGame);
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