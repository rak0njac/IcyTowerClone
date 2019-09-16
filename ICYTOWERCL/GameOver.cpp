#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowEngine.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

static bool gameOver;
static RainbowText textGameOver("GAME OVER!", DefaultFont::getFont(), 168);
static RainbowText textFloor("", DefaultFont::getFont(), 60);
static RainbowText textBestCombo("", DefaultFont::getFont(), 60);
static RainbowText textPressEnter("PRESS ENTER TO RESTART...", DefaultFont::getFont(), 60);

static sf::SoundBuffer sbGameOver;
static sf::SoundBuffer sbTryAgain;
static sf::Sound sound;

static sf::Vector2i values;		//floor and best combo values

void GameOver::init()
{
	gameOver = false;

	textGameOver.setOutlineThickness(7);
	textGameOver.setScale(0.5, 0.5);
	textGameOver.setOrigin(textGameOver.getLocalBounds().width / 2, textGameOver.getLocalBounds().height / 2);
	textGameOver.setPosition(320, -140);
	textGameOver.setOutlineColor(sf::Color(1, 26, 51, 255));
	
	textFloor.setOutlineThickness(4);
	textFloor.setScale(0.5, 0.5);
	textFloor.setPosition(320, 500);
	
	textBestCombo.setOutlineThickness(4);
	textBestCombo.setScale(0.5, 0.5);
	textBestCombo.setPosition(320, 530);
	
	textPressEnter.setOutlineThickness(4);
	textPressEnter.setScale(0.5, 0.5);
	textPressEnter.setOrigin(textPressEnter.getLocalBounds().width / 2, textPressEnter.getLocalBounds().height / 2);
	textPressEnter.setPosition(320, 500);

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
	if (textGameOver.getPosition().y < 180)
	{
		textGameOver.move(0, 4);
	}
	if (textFloor.getPosition().y > 360)
		textFloor.move(0, -2);
	if (textBestCombo.getPosition().y > 390)
		textBestCombo.move(0, -2);
	else if (textPressEnter.getPosition().y > 450)
		textPressEnter.move(0, -2);
}

void GameOver::reset()
{
	textGameOver.setPosition(320, -140);
	textFloor.setPosition(320, 500);
	textBestCombo.setPosition(320, 530);
	textPressEnter.setPosition(320, 500);

	textFloor.setString("FLOOR: " + std::to_string(values.x));
	textFloor.setOrigin(textFloor.getLocalBounds().width * 0.5, textFloor.getLocalBounds().height * 0.5);
	textBestCombo.setString("BEST COMBO: " + std::to_string(values.y));
	textBestCombo.setOrigin(textBestCombo.getLocalBounds().width * 0.5, textBestCombo.getLocalBounds().height * 0.5);
}