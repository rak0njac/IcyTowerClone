#pragma once
#include "EyeCandy.h"
#include <PlatformLayer.h>
#include <vector>
class EyeCandyEngine
{
private:
	std::vector<EyeCandy> engine;
public:
	EyeCandyEngine();
	void addCandy(float posX, float posY);
	void doLogic(sf::RenderWindow& window, PlatformLayer& pl);
};

