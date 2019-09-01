#include <GameOver.h>
#include <Camera.h>
#include <Timer.h>
#include <Score.h>
#include <RainbowEngine.h>
#include <Background.h>
#include <Player.h>
#include <Game.h>

bool GameOver::gameOver = false;

using namespace GameOver;

bool GameOver::isGameOver() { return gameOver; }

void GameOver::stopGame()
{
	Camera::stop();
	Score::stop();
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