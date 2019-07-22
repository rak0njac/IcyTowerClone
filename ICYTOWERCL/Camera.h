#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <Platform.h>

namespace Camera
{
	extern int camSpeed;
	extern int startStep;
	extern float camSpeedFactor;

	void catchUp(float playerPos);
}


#endif