#include <Game.h>
#include <RainbowEngine.h>

//basic init
sf::RenderWindow window(sf::VideoMode(640, 480), "Icy Tower Clone // Written in C++ using SFML", sf::Style::Close);
sf::Event event;

//object init
sf::Music music;
Player player;
Layer Game::Layers::layerBkg;
Layer Game::Layers::layerWall(3);
Layer Game::Layers::layerHurryText(0);
PlatformEngine Game::Layers::platformEngine(2);
Layer Game::Layers::layerHud(0);

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
					if (gameState == Game::State::GameOver)
					{
						GameOver::restartGame();
					}
				}
			}
		}

		if (gameState == Game::State::InGame)
		{
			window.clear();

			//logic processing
			Layers::layerBkg.logic();
			Layers::layerWall.logic();
			Layers::platformEngine.logic();
			Timer::logic();
			Score::logic();
			player.logic();

			//rendering (in order)
			Background::render(window, Background::Sprites::Background);
			Timer::render(window, Timer::Sprites::HurryUpText);
			Layers::platformEngine.render(window);
			Background::render(window, Background::Sprites::Wall);
			player.render(window);
			Score::render(window);
			Timer::render(window, Timer::Sprites::Clock);

			window.display();
		}
		//else if (gameState ==  State::GameOver)
		//{ 
		//	window.clear();

		//	layerBkg.render(window, Background::Sprite::spBkg);
		//	layerPlatform.render(window);
		//	player.logic();
		//	player.render(window, layerPlatform); //work on
		//	layerWall.render(window, Background::Sprite::spWall);
		//	Score::logic();
		//	Score::render(window, layerHud);

		//	//layerHud.render(window, Timer::SpClock);
		//	//layerHud.render(window, Timer::SpClockHandle);
		//	GameOver::logic();
		//	GameOver::render(window, layerHud);

		//	window.display();
		//}
		//else if (gameState == State::Resetting)
		//{
		//	static int i = 0;
		//	static int phase = 0;
		//	if (phase == 0)
		//	{
		//		music.stop();
		//		GameOver::reset();
		//		phase++;
		//	}
		//	else if (phase == 1)
		//	{
		//		if (i < 51)
		//		{
		//			window.clear();

		//			layerBkg.render(window, Background::Sprite::spBkg);
		//			layerPlatform.render(window);
		//			player.render(window, layerPlatform);
		//			layerWall.render(window, Background::Sprite::spWall);
		//			Score::render(layerHud, window);

		//			//layerHud.render(window, Timer::SpClock);
		//			//layerHud.render(window, Timer::SpClockHandle);

		//			GameOver::render(window, layerHud);
		//			FadeEffect::fade(i * 5);
		//			layerHud.render(window, FadeEffect::getDrawable()); //CHECK
		//			window.display();

		//			i++;
		//		}
		//		else phase++;
		//	}
		//	else if (phase == 2)
		//	{
		//		Background::reset();
		//		player.reset();
		//		Score::reset();
		//		Timer::reset();
		//		Game::reset();

		//		music.stop();
		//		window.clear();

		//		layerBkg.render(window, Background::Sprite::spBkg);
		//		layerPlatform.render(window);
		//		player.logic();
		//		player.render(window, layerPlatform);
		//		layerWall.render(window, Background::Sprite::spWall);
		//		Timer::logic();
		//		Score::logic();

		//		Score::render(window, layerHud);

		//		//layerHud.render(window, Timer::SpClock);
		//		//layerHud.render(window, Timer::SpClockHandle);
		//		phase++;
		//	}
		//	else if (phase == 3)
		//	{
		//		if (i > 0)
		//		{
		//			window.clear();

		//			layerBkg.render(window, Background::Sprite::spBkg);
		//			layerPlatform.render(window); //layerplatform -- layerengine?
		//			player.render(window, layerPlatform);
		//			layerWall.render(window, Background::Sprite::spWall);
		//			Score::render(window, layerHud);

		//			//layerHud.render(window, Timer::SpClock);
		//			//layerHud.render(window, Timer::SpClockHandle);
		//			GameOver::render(window, layerHud);
		//			FadeEffect::fade(i * 5);
		//			layerHud.render(window, FadeEffect::getDrawable());
		//			window.display();

		//			i--;
		//		}
		//		else phase++;
		//	}
		//	else if (phase == 4)
		//	{
		//		music.play();
		//		setState(Game::State::InGame);
		//		phase = 0;
		//		//done!
		//	}
		//}
		else if (gameState == Game::State::Loading)
		{
			window.setFramerateLimit(100);
			window.setKeyRepeatEnabled(false);

			music.openFromFile("..\\Assets\\Sounds\\beat.ogg");
			music.setLoop(true);
			music.setVolume(70);

			DefaultFont::init();
			RainbowText re("LOADING...", DefaultFont::getFont(), 140);
			re.setOrigin(re.getLocalBounds().width * 0.5, re.getLocalBounds().height * 0.5);
			re.setPosition(320, 240);
			re.textMagic();
			//Layers::layerHud.render(window);

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
	Layers::layerBkg.reset();
	Layers::layerWall.reset();
	Layers::layerHud.reset();
	Layers::platformEngine.reset();
}