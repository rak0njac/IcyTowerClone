#pragma once
#include <iostream>

namespace Camera
{
	//int camLevel;
	//float camSpeed;

	int getCamLevel();
	float getCamSpeed();
	void setCamLevel(int value);
	void setCamSpeed(float value);
	void stop();
}