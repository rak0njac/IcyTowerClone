#include "Layer.h"
#include <Platform.h>
#include <vector>

#pragma once
class PlatformEngine : public Layer
{
public:
	static Platform arrPlatform[7];
	void logic();
	void render(sf::RenderWindow& window);
	PlatformEngine(float speedDelta) :Layer(speedDelta) {}

	void reset();
};