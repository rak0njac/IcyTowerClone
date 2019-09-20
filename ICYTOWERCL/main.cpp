#include <Game.h>

//platform floor number fix
//multiple textures in one image
//add platform variations
//add boom when player falls

//wherever there is posiiton, cast to int
//separate logic from render in eyecandyengine

int main()
{
	Game::init();
	Game::logic();
	return 0;
}