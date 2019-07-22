#include "PlatformLayer.h"

Platform PlatformLayer::arrPlatform[7]{ 1, 2, 3, 4, 5, 6, 7 };

void PlatformLayer::move(float camSpeedFactor, int camSpeed)
{
	view.reset(sf::FloatRect(0, CamY, 640, 480));
	CamY -= camSpeedFactor * camSpeed * speedFactor;
	step -= camSpeed;
	const float y = view.getCenter().y - 190;					// 190 is the number of pixels from the bottom edge od the window 
																// to the top edge of the first platform
	for (Platform p : arrPlatform)
	{
		static bool thruFirstPlatform = false;
		static int yFactor = 0;
		static int level = 1;
		if (!thruFirstPlatform && y <= 0)
		{
			thruFirstPlatform = true;
		}
		else if (thruFirstPlatform && y <= arrPlatform[0].yDistance * yFactor)
		{

			for (int i = 0; i < 7; i++)
			{
				if (arrPlatform[i].floor == level) {
					arrPlatform[i].regenerate();
				}
			}
			yFactor--;
			level++;
		}
	}

}

//void PlatformLayer::collide(sf::Sprite& player)
//{
//	for (Platform p : arrPlatform)
//	{
//		if (player.getTextureRect().intersects(p.middleSp.getTextureRect()))
//		{
//			player.setPosition(320, 240);
//		}
//
//	}
//}

void PlatformLayer::render(sf::RenderWindow& window)
{
	window.setView(view);
	for (Platform p : arrPlatform)
	{
		p.render(window);			
	}
}
