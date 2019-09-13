#include "Layer.h"
#include <Platform.h>
#include <vector>

#pragma once
class PlatformLayer : public Layer
{
public:
	static Platform arrPlatform[7];//std::vector<Platform> arrPlatform;
	void move();
	void render(sf::RenderWindow& window);
	void render(sf::RenderWindow& window, sf::Drawable& drawable);
	PlatformLayer(float speedDelta) :Layer(speedDelta) {}

	void reset();
};