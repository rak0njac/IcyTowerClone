#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Background.h>
#include <Camera.h>
#include <Player.h>
#include <Timer.h>
#include <Score.h>
#include <EyeCandy.h>
#include <iostream>
#include <DefaultFont.h>
#include <GameOver.h>
#include <RainbowText.h>

namespace Game
{
	//sf::RenderWindow window;
	//sf::Event event;

	//Player player;
	//Layer layerBkg;
	//Layer layerWall;
	//PlatformLayer layerPlatform;
	//Layer layerHud;

	//bool debug;

	enum State
	{
		InGame,
		GameOver,
		Resetting,
		Loading
	};

	namespace Layers
	{
		extern Layer Background;
		extern Layer Wall;
		//extern Layer layerHurryText;
		extern Layer HUD;
		extern PlatformEngine Platforms;
	}

	void init();
	void setState(int state);
	int getState();
	void logic();
	void reset();
}
