#include "DefaultFont.h"

sf::Font DefaultFont::font;

void DefaultFont::init()
{
	font.loadFromFile("..\\Assets\\freshmarker.ttf");
}														//SFML uses automatic text smoothing which applies a smoothing filter that is extremely strong
														//and aesthetically unpleasant. This is why for most of the text we will be using double the font sizes
														//and then scale the text halfway down. This eliminates the awkward smoothing. This is a known
														//issue with SFML with no known proper solutions. This is the best workaround I could come up with,
														//even though double font sizes use significantly more memory.
const sf::Font& DefaultFont::getFont()											
{
	return font;
}