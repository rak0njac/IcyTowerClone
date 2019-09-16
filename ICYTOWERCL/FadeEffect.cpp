#include <FadeEffect.h>
#include <iostream>

sf::RectangleShape black(sf::Vector2f(640,480));

void FadeEffect::init()
{
	black.setFillColor(sf::Color(0, 0, 0, 1));
}

//1. press enter
//2. stop clearing and doing logic, only draw and display
//3. on every tick, fade in black by 1
//4. when alpha is 255, reset the game, but still no logic-- - on game reset stop music!
//5. clear the screen and redraw everything only once
//6. on every tick, fade out black by 1
//7. when alpha is 0, start clearing and redrawing on every tick
//8. play 'yo' and music.

void FadeEffect::fade(int alpha)
{
	black.setFillColor(sf::Color(0, 0, 0, alpha));
}

bool FadeEffect::fadeIn()
{
	static int i = 0;
	if (i < 255)
	{
		black.setFillColor(sf::Color(0,0,0,i));
		std::cout << black.getFillColor().a;
		i++;
		return false;
	}
	else if(i==256)
	{
		return false;
	}
	else
	{
		i = 256;
		return true;
	}
}

bool FadeEffect::fadeOut()
{
	static int i = 25;
	if (i > 0)
	{
		//colora.a = i;
		i--;
		return false;
	}
	else
	{
		return true;
	}
}

sf::Drawable& FadeEffect::getDrawable()
{
	return black;
}