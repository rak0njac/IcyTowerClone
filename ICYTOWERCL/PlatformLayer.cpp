#include "PlatformLayer.h"
#include <iostream>

Platform PlatformLayer::arrPlatform[7]{ 1, 2, 3, 4, 5, 6, 7 };

void PlatformLayer::move()
{						
	float camSpeed = Camera::getCamSpeed();
	static int i = 0;
	view.reset(sf::FloatRect(0, camY, 640, 480));
	camY -= const_cam_speed_delta * camSpeed * speedDelta;
	step -= camSpeed;

	if (view.getCenter().y - 270 <= const_dist_between_platforms * (arrPlatform[i].getFloor()) * -1)		// CONST_FROM_BOTTOM_OF_WINDOW_TO_TOP_OF_FIRST_PLATFORM = 190 
	{																						// is the number of pixels from the bottom edge od the window 
		arrPlatform[i].regenerate();														// to the top edge of the first platform
		if (i < 6)
			i++;
		else i = 0;
	}
}

void PlatformLayer::render(sf::RenderWindow& window)
{
	window.setView(view);
	for (Platform& p : arrPlatform)
	{
		p.render(window);			
	}
}

float PlatformLayer::getViewCenter()
{
	return view.getCenter().y;
}