#include "PlatformLayer.h"
#include <iostream>

//std::vector<Platform> PlatformLayer::arrPlatform;
Platform PlatformEngine::arrPlatform[7]{ 1, 2, 3, 4, 5, 6, 7 };
int index = 0;

void PlatformEngine::logic()
{						
	float camSpeed = Camera::getCamSpeed();
	view.reset(sf::FloatRect(0, camPosY, 640, 480));
	camPosY -= const_cam_speed_delta * camSpeed * speedDelta;
	step -= camSpeed;
	//std::cout << arrPlatform[index].getFloor() << '\n';

	if (view.getCenter().y - 270 <= const_dist_between_platforms * (arrPlatform[index].getFloor()) * -1)
	{																					
		arrPlatform[index].regenerate();												
		if (index < 6)
			index++;
		else index = 0;
	}
}

void PlatformEngine::render(sf::RenderWindow& window)
{
	window.setView(view);
	for (Platform& p : arrPlatform)
	{
		p.render(window);
	}
}

void PlatformEngine::reset()
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	camPosY = 0;
	index = 0;
	step = conststep;
	
	for (int i = 0; i < 7; i++)
	{
		arrPlatform[i].reset(i + 1);
	}
}