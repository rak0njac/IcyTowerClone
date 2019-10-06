#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowText.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

static bool gameOver;
static bool boomScreenShaking;
static bool playerFell;
static float boomTime;
static RainbowText rtGameOver("GAME OVER!", DefaultFont::getFont(), const_text_size_large);
static RainbowText rtFloor("", DefaultFont::getFont(), const_text_size_medium);
static RainbowText rtBestCombo("", DefaultFont::getFont(), const_text_size_medium);
static RainbowText rtPressEnter("PRESS ENTER TO RESTART...", DefaultFont::getFont(), const_text_size_medium);

static sf::SoundBuffer sbGameOver;
static sf::SoundBuffer sbTryAgain;
static sf::SoundBuffer sbBoom;
static sf::Sound sound;

static sf::Vector2i values;		//floor and best combo values

static Layer& curLayer = Game::Layers::HUD;

static sf::Clock goClock;

void GameOver::init()
{
	gameOver = false;
	playerFell = false;
	boomScreenShaking = false;
	boomTime = 0;

	rtGameOver.init();
	rtGameOver.setOutlineThickness(const_text_outline_large);
	rtGameOver.setScale(0.6, 0.6);
	rtGameOver.setOrigin(rtGameOver.getLocalBounds().width / 2, rtGameOver.getLocalBounds().height / 2);
	rtGameOver.setPosition(320, -140);
	rtGameOver.setOutlineColor(sf::Color(1, 26, 51, 255));
	rtGameOver.setLayer(curLayer);

	rtFloor.init();
	rtFloor.setOutlineThickness(const_text_outline_medium);
	//rtFloor.setScale(0.5, 0.5);
	rtFloor.setPosition(320, 500);
	rtFloor.setLayer(curLayer);

	rtBestCombo.init();
	rtBestCombo.setOutlineThickness(const_text_outline_medium);
	//rtBestCombo.setScale(0.5, 0.5);
	rtBestCombo.setPosition(320, 530);
	rtBestCombo.setLayer(curLayer);

	rtPressEnter.init();
	rtPressEnter.setOutlineThickness(const_text_outline_medium);
	//rtPressEnter.setScale(0.5, 0.5);
	rtPressEnter.setOrigin(rtPressEnter.getLocalBounds().width / 2, rtPressEnter.getLocalBounds().height / 2);
	rtPressEnter.setPosition(320, 500);
	rtPressEnter.setLayer(curLayer);

	sbGameOver.loadFromFile("..\\Assets\\Sounds\\gameover.ogg");
	sbTryAgain.loadFromFile("..\\Assets\\Sounds\\tryagain.ogg");
	sbBoom.loadFromFile("..\\Assets\\Sounds\\boom.ogg");
}

bool GameOver::isGameOver() { return gameOver; }

void GameOver::stopGame()
{
	sound.setBuffer(sbGameOver);
	sound.play();

	Game::setState(Game::State::GameOver);

	Camera::stop();
	values = Score::stop();

	rtFloor.setString("FLOOR: " + std::to_string(values.x));
	rtFloor.setOrigin(rtFloor.getLocalBounds().width / 2, rtFloor.getLocalBounds().height / 2);
	rtBestCombo.setString("BEST COMBO: " + std::to_string(values.y));
	rtBestCombo.setOrigin(rtBestCombo.getLocalBounds().width / 2, rtBestCombo.getLocalBounds().height / 2);

	gameOver = true;

	boomTime = values.x / 10.0f;
	if (boomTime > 5)
		boomTime = 5;

	goClock.restart();
}

void GameOver::restartGame()
{
	sound.setBuffer(sbTryAgain);
	sound.play();
	Game::setState(Game::State::Resetting);

	gameOver = false;
}

void GameOver::logic()
{
	if (rtGameOver.getPosition().y < 180)
	{
		rtGameOver.move(0, 4);
	}
	if (rtFloor.getPosition().y > 360)
		rtFloor.move(0, -2);
	if (rtBestCombo.getPosition().y > 390)
		rtBestCombo.move(0, -2);
	else if (rtPressEnter.getPosition().y > 450)
		rtPressEnter.move(0, -2);							

	rtGameOver.logic();
	rtFloor.logic();
	rtBestCombo.logic();
	rtPressEnter.logic();

	if (!playerFell && goClock.getElapsedTime().asSeconds() > boomTime)
	{
		Player::stopScreaming();
		sound.setBuffer(sbBoom);
		sound.play();
		playerFell = true;
		boomScreenShaking = true;
	}

	if (boomScreenShaking)
	{
		static int step = 0;
		static int side = -1;
		if (step < 50)
		{
			if (step % 3 == 0)
				side *= -1;

			if (side == 1)
				Camera::setCamSpeed(10);
			else Camera::setCamSpeed(-10);
			step++;
		}
		else
		{
			step = 0;
			side = -1;
			boomScreenShaking = false;
			Camera::setCamSpeed(0);
		}
	}
}

void GameOver::render(sf::RenderWindow& window)
{
	rtGameOver.setOrigin((int)rtGameOver.getOrigin().x, (int)rtGameOver.getOrigin().y);
	rtFloor.setOrigin((int)rtFloor.getOrigin().x, (int)rtFloor.getOrigin().y);
	rtBestCombo.setOrigin((int)rtBestCombo.getOrigin().x, (int)rtBestCombo.getOrigin().y);
	rtPressEnter.setOrigin((int)rtPressEnter.getOrigin().x, (int)rtPressEnter.getOrigin().y);

	rtGameOver.render(window);
	rtFloor.render(window);
	rtBestCombo.render(window);
	rtPressEnter.render(window);
}

void GameOver::reset()
{
	rtGameOver.setPosition(320, -140);
	rtFloor.setPosition(320, 500);
	rtBestCombo.setPosition(320, 530);
	rtPressEnter.setPosition(320, 500);

	playerFell = false;
	boomScreenShaking = false;
	boomTime = 0;
}