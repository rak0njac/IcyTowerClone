#include <Game.h>

//basic init
sf::RenderWindow window(sf::VideoMode(640, 480), "Icy Tower Clone // Written in C++ using SFML - v1.0", sf::Style::Close);
sf::Event event;

//object init
sf::Music music;
Player player;
Layer Game::Layers::Background;
Layer Game::Layers::Wall(3);
PlatformEngine Game::Layers::Platforms(2);
Layer Game::Layers::HUD(0);

int gameState;

void Game::init()
{
	setState(Game::State::Loading);
}

void Game::setState(int state)
{
	gameState = state;
}

int Game::getState()
{
	return gameState;
}

void Game::logic()
{
	while (window.isOpen())
	{
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (gameState == Game::State::GameOver)
					{
						GameOver::restartGame();
					}
				}
				else if (event.key.code == sf::Keyboard::Q)
				{
					window.setFramerateLimit(5);
				}
			}
		}

		if (gameState == Game::State::InGame)
		{
			window.clear();

			//logic processing
			Layers::Background.logic();
			Layers::Wall.logic();
			Layers::Platforms.logic();
			Timer::logic();
			player.logic();
			Score::logic();

			//rendering (in order)
			Background::render(window, Background::Sprites::Background);
			Timer::render(window, Timer::Sprites::HurryUpText);
			Layers::Platforms.render(window);
			player.render(window);
			Background::render(window, Background::Sprites::Wall);
			Score::render(window);
			Timer::render(window, Timer::Sprites::Clock);

			window.display();
		}
		else if (gameState == State::GameOver)
		{
			window.clear();

			Layers::Background.logic();
			Layers::Wall.logic();
			Layers::Platforms.logic();
			player.logic();
			Score::logic();
			GameOver::logic();

			Background::render(window, Background::Sprites::Background);
			Layers::Platforms.render(window);
			player.render(window);	//mostly for eye candy stars
			Background::render(window, Background::Sprites::Wall);
			Score::render(window);
			Timer::render(window, Timer::Sprites::Clock);
			GameOver::render(window);

			window.display();
		}
		else if (gameState == State::Resetting)
		{
			static int step = 0;
			static int phase = 0;
			static sf::RectangleShape black(sf::Vector2f(640, 480));

			if (phase == 0)
			{
				music.stop();
				GameOver::reset();
				phase++;
			}
			else if (phase == 1)
			{
				black.setFillColor(sf::Color(0, 0, 0, 1));

				if (step < 51)
				{
					window.clear();

					Background::render(window, Background::Sprites::Background);
					Layers::Platforms.render(window);
					player.render(window);
					Background::render(window, Background::Sprites::Wall);
					Score::render(window);
					Timer::render(window, Timer::Sprites::Clock);
					GameOver::render(window);

					black.setFillColor(sf::Color(0, 0, 0, step * 5));

					Layers::HUD.render(window, black);

					window.display();

					step++;
				}
				else phase++;
			}
			else if (phase == 2)
			{
				Background::reset();
				player.reset();
				Score::reset();
				Timer::reset();
				Game::reset();
				Camera::stop();

				music.stop();
				//window.clear();

				player.logic();
				Score::logic();
				Timer::logic();

				Background::render(window, Background::Sprites::Background);
				Layers::Platforms.render(window);
				player.render(window);
				Background::render(window, Background::Sprites::Wall);
				Score::render(window);
				Timer::render(window, Timer::Sprites::Clock);

				phase++;
			}
			else if (phase == 3)
			{
				if (step > 0)
				{
					window.clear();

					Background::render(window, Background::Sprites::Background);
					Layers::Platforms.render(window);
					player.render(window);
					Background::render(window, Background::Sprites::Wall);
					Score::render(window);
					Timer::render(window, Timer::Sprites::Clock);

					black.setFillColor(sf::Color(0, 0, 0, step * 5));
					Layers::HUD.render(window, black);

					window.display();

					step--;
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
			//sf::Listener s;
			//s.setGlobalVolume(0);

			music.openFromFile("..\\Assets\\Sounds\\beat.ogg");
			music.setLoop(true);
			music.setVolume(70);

			DefaultFont::init();
			sf::Text textLoading("LOADING...", DefaultFont::getFont(), const_text_size_large);
			textLoading.setOrigin(textLoading.getLocalBounds().width / 2, textLoading.getLocalBounds().height / 2);
			textLoading.setPosition(320, 240);
			window.draw(textLoading);

			window.display();

			Background::init();
			Timer::init();
			Score::init();
			GameOver::init();
			player.init();
			music.play();
			Platform::init();

			setState(Game::State::InGame);
		}
	}
}

void Game::reset()
{
	Layers::Background.reset();
	Layers::Wall.reset();
	Layers::HUD.reset();
	Layers::Platforms.reset();
}