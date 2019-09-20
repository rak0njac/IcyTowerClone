#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowText.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

static bool gameOver;
static RainbowText rtGameOver("GAME OVER!", DefaultFont::getFont(), 168);
static RainbowText rtFloor("", DefaultFont::getFont(), 60);
static RainbowText rtBestCombo("", DefaultFont::getFont(), 60);
static RainbowText rtPressEnter("PRESS ENTER TO RESTART...", DefaultFont::getFont(), 60);

static sf::SoundBuffer sbGameOver;
static sf::SoundBuffer sbTryAgain;
static sf::Sound sound;

static sf::Vector2i values;		//floor and best combo values

static Layer& curLayer = Game::Layers::HUD;

void GameOver::init()
{
	gameOver = false;

	rtGameOver.init();
	rtGameOver.setOutlineThickness(7);
	rtGameOver.setScale(0.5, 0.5);
	rtGameOver.setOrigin(rtGameOver.getLocalBounds().width / 2, rtGameOver.getLocalBounds().height / 2);
	rtGameOver.setPosition(320, -140);
	rtGameOver.setOutlineColor(sf::Color(1, 26, 51, 255));
	rtGameOver.setLayer(curLayer);
	
	rtFloor.init();
	rtFloor.setOutlineThickness(4);
	rtFloor.setScale(0.5, 0.5);
	rtFloor.setPosition(320, 500);
	rtFloor.setLayer(curLayer);
	
	rtBestCombo.init();
	rtBestCombo.setOutlineThickness(4);
	rtBestCombo.setScale(0.5, 0.5);
	rtBestCombo.setPosition(320, 530);
	rtBestCombo.setLayer(curLayer);
	
	rtPressEnter.init();
	rtPressEnter.setOutlineThickness(4);
	rtPressEnter.setScale(0.5, 0.5);
	rtPressEnter.setOrigin(rtPressEnter.getLocalBounds().width / 2, rtPressEnter.getLocalBounds().height / 2);
	rtPressEnter.setPosition(320, 500);
	rtPressEnter.setLayer(curLayer);

	sbGameOver.loadFromFile("..\\Assets\\Sounds\\gameover.ogg");
	sbTryAgain.loadFromFile("..\\Assets\\Sounds\\tryagain.ogg");
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
}

void GameOver::render(sf::RenderWindow& window)
{
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
}