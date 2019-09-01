#include <SFML/Graphics.hpp>
#include <Background.h>
#include <Camera.h>
#include <Player.h>
#include <Timer.h>
#include <Score.h>
#include <EyeCandy.h>
#include <iostream>
#include <Font.h>
#include <GameOver.h>
#include <Game.h>

//brzine 1,2,4,6,9,11
//text scaling instead of font size
//Add comments?

//game over
//start screen
//launcher in qt?
//audio
//platform floor % 10 = 0 show -- to fix
//multiple textures in one image
//add platform variations

int main()
{
	Game::init();
	Game::logic();
	return 0;
}