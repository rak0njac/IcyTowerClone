#include "Layer.h"
#include <Platform.h>
#pragma once
class PlatformLayer : public Layer
{
public:
	static Platform arrPlatform[7];
	void move();
	void render(sf::RenderWindow& window);
	float getViewCenter();
	PlatformLayer(float speedDelta) :Layer(speedDelta) {}
};