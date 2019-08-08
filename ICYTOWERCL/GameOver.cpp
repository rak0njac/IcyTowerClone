#include <GameOver.h>

bool GameOver::gameOver = false;

using namespace GameOver;

bool GameOver::isGameOver() { return gameOver; }

void GameOver::restartGame()
{
	//Background::reset();
	//Layer::reset();
	//PlatformLayer::reset();
	//Platform::reset();
	//Player::reset();
	//Score::reset();
	//Timer::reset();
}