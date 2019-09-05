#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowEngine.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

bool gameOver = false;
sf::Text textGameOver("GAME OVER!", Font::getFont(), 168);
sf::Text textFloor("", Font::getFont(), 60);
sf::Text textBestCombo("", Font::getFont(), 60);
sf::Text textPressEnter("PRESS ENTER TO RESTART...", Font::getFont(), 60);
RainbowEngine reGameOver(textGameOver);
RainbowEngine reFloor(textFloor);
RainbowEngine reBestCombo(textBestCombo);
RainbowEngine rePressEnter(textPressEnter);

sf::Vector2i values;

void GameOver::init()
{
	textGameOver.setOutlineThickness(7);
	textGameOver.setScale(0.5, 0.5);
	textGameOver.setOrigin(textGameOver.getLocalBounds().width * 0.5, textGameOver.getLocalBounds().height * 0.5);
	textGameOver.setPosition(320, -140);
	textGameOver.setOutlineColor(sf::Color(1, 26, 51, 255));

	textFloor.setOutlineThickness(4);
	textFloor.setScale(0.5, 0.5);
	textFloor.setPosition(320, 500);
	//textFloor.setOutlineColor(sf::Color(1, 26, 51, 255));

	textBestCombo.setOutlineThickness(4);
	textBestCombo.setScale(0.5, 0.5);
	textBestCombo.setPosition(320, 530);

	textPressEnter.setOutlineThickness(4);
	textPressEnter.setScale(0.5, 0.5);
	textPressEnter.setOrigin(textPressEnter.getLocalBounds().width * 0.5, textPressEnter.getLocalBounds().height * 0.5);
	textPressEnter.setPosition(320, 500);
}

bool GameOver::isGameOver() { return gameOver; }

void GameOver::stopGame()
{
	Camera::stop();
	values = Score::stop();
	gameOver = true;
}

void GameOver::restartGame()
{
	Background::reset();
	Score::reset();
	Timer::reset();
	Game::reset();
	gameOver = false;
}

void GameOver::doLogic()
{
	if (gameOver)
	{
		textFloor.setString("FLOOR: " + std::to_string(values.x));
		textFloor.setOrigin(textFloor.getLocalBounds().width * 0.5, textFloor.getLocalBounds().height * 0.5);
		textBestCombo.setString("BEST COMBO: " + std::to_string(values.y));
		textBestCombo.setOrigin(textBestCombo.getLocalBounds().width * 0.5, textBestCombo.getLocalBounds().height * 0.5);

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
	else
	{
		textGameOver.setPosition(320, -140);
		textFloor.setPosition(320, 500);
		textBestCombo.setPosition(320, 530);
		textPressEnter.setPosition(320, 500);
	}
}

void GameOver::render(sf::RenderWindow& window)
{
	//if(gameOver) -- render always but outside of view if not game over. 
	//Workaround for text appearing in the middle for one frame on every game over.
	//if too expensive find proper solution?
		reGameOver.textMagic(window);
		reFloor.textMagic(window);
		reBestCombo.textMagic(window);
		rePressEnter.textMagic(window);
}