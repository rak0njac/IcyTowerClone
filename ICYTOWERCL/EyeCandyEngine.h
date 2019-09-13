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
	void addCandy(const float& posX, const float& posY, int count);
	void addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, int count);
	void addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed, int count);
	void doLogic(sf::RenderWindow& window, Layer& pl);
	void reset();
};

