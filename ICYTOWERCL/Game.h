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
#include <Font.h>
#include <GameOver.h>
#include <FadeEffect.h>

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
		extern Layer layerBkg;
		extern Layer layerWall;
		extern Layer layerHurryText;
		extern Layer layerHud;
		extern PlatformEngine platformEngine;
	}

	void init();
	void setState(int state);
	void logic();
	void reset();
}
