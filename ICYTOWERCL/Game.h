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

	extern PlatformLayer layerPlatform;
	extern Layer layerHud;

	void init();
	void logic();
	void reset();
}
