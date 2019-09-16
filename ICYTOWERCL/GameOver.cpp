#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowEngine.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

bool gameOver = false;
bool gameOverReset = false;
RainbowEngine textGameOver("GAME OVER!", Font::getFont(), 168);
RainbowEngine textFloor("", Font::getFont(), 60);
RainbowEngine textBestCombo("", Font::getFont(), 60);
RainbowEngine textPressEnter("PRESS ENTER TO RESTART...", Font::getFont(), 60);
RainbowEngine reGameOver("GAME OVER!", Font::getFont(), 168);
RainbowEngine reFloor("", Font::getFont(), 60);
RainbowEngine reBestCombo("", Font::getFont(), 60);
RainbowEngine rePressEnter("PRESS ENTER TO RESTART...", Font::getFont(), 60);

sf::SoundBuffer sbGameOver;
sf::SoundBuffer sbTryAgain;
static sf::Sound sound;

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
	//rextFloor.setOutlineColor(sf::Color(1, 26, 51, 255));
	
	textBestCombo.setOutlineThickness(4);
	textBestCombo.setScale(0.5, 0.5);
	textBestCombo.setPosition(320, 530);
	
	textPressEnter.setOutlineThickness(4);
	textPressEnter.setScale(0.5, 0.5);
	textPressEnter.setOrigin(textPressEnter.getLocalBounds().width * 0.5, textPressEnter.getLocalBounds().height * 0.5);
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

void GameOver::doLogic()
{
	if (gameOver)
	{
		if (!gameOverReset)
		{
			textFloor.setString("FLOOR: " + std::to_string(values.x));
			textFloor.setOrigin(textFloor.getLocalBounds().width * 0.5, textFloor.getLocalBounds().height * 0.5);
			textBestCombo.setString("BEST COMBO: " + std::to_string(values.y));
			textBestCombo.setOrigin(textBestCombo.getLocalBounds().width * 0.5, textBestCombo.getLocalBounds().height * 0.5);
			gameOverReset = true;
		}

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
}

void GameOver::reset()
{
	textGameOver.setPosition(320, -140);
	textFloor.setPosition(320, 500);
	textBestCombo.setPosition(320, 530);
	textPressEnter.setPosition(320, 500);
	gameOverReset = false;
}

void GameOver::render(sf::RenderWindow& window, Layer& layer)
{
	//if(gameOver) -- render always but outside of view if not game over. 
	//Workaround for text appearing in the middle for one frame on every game over.
	//if too expensive find proper solution?
	if (gameOver)
	{
		textGameOver.textMagic(window, layer);
		textFloor.textMagic(window, layer);
		textBestCombo.textMagic(window, layer);
		textPressEnter.textMagic(window, layer);
	}

}