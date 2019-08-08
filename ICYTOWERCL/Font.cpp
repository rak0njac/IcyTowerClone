#include "Font.h"

sf::Font Font::font;

void Font::init()
{
	font.loadFromFile("..\\Assets\\freshmarker.ttf");
	const_cast<sf::Texture&>(font.getTexture(20)).setSmooth(false); //sfml doesn't provide a way to disable anti-aliasing on fonts so we have to use
	const_cast<sf::Texture&>(font.getTexture(30)).setSmooth(false); //this well known hack. since getTexture() is used only internally by sf::Text,
}																	//iterating through all font sizes will load all textures for each font size
																	//hence we disable smoothing only on the sizes we use. even this way it doesn't
sf::Font& Font::getFont()											//work as expected but it's better than nothing.
{
	return font;
}