#include <FadeEffect.h>

//maybe delete this file...
sf::RectangleShape black(sf::Vector2f(640,480));

void FadeEffect::init()
{
	black.setFillColor(sf::Color(0, 0, 0, 1));
}

void FadeEffect::fade(int alpha)
{
	black.setFillColor(sf::Color(0, 0, 0, alpha));
}

sf::Drawable& FadeEffect::getDrawable()
{
	return black;
}