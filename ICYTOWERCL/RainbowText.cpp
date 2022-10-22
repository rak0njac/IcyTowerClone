#include "RainbowText.h"

void RainbowText::init()
{
	colorsInitialized = false;
	charsInitialized = false;

	numOfChars = this->getString().getSize();
	for (int i = 0; i < numOfChars; i++)	//push each character individually into the chars vector
		chars.push_back(sf::Text(this->getString().substring(i, 1), DefaultFont::getFont(), this->getCharacterSize()));
	comp = *this;

	numOfColors = 18;
	while (numOfColors < numOfChars)	//clean this shit up - see textMagic()
		numOfColors += 18;

	layer = nullptr;
	magicSkipper = false;
	magicX = 0;
	magicY = 0;

	getLocalBounds();

	initialized = true;
}

sf::Color RainbowText::changeColor(const sf::Color& color, const int delta)
{
	//tempstore the original color values
	int colR = color.r;
	int colG = color.g;
	int colB = color.b;

	//color changing logic
	if (color.r == 255 && color.g < 255 && color.b == 0)
		colG += delta;
	else if (color.r > 0 && color.g == 255 && color.b == 0)
		colR -= delta;
	else if (color.r == 0 && color.g == 255 && color.b < 255)
		colB += delta;
	else if (color.r == 0 && color.g > 0 && color.b == 255)
		colG -= delta;
	else if (color.r < 255 && color.g == 0 && color.b == 255)
		colR += delta;
	else if (color.r == 255 && color.g == 0 && color.b > 0)
		colB -= delta;

	//rgb values cant be greater than 255 or lesser than 0 or else undefined behavior
	if (colR > 255)
		colR = 255;
	if (colG > 255)
		colG = 255;
	if (colB > 255)
		colB = 255;
	if (colR < 0)
		colR = 0;
	if (colG < 0)
		colG = 0;
	if (colB < 0)
		colB = 0;

	//create color of new values
	sf::Color out;
	out.r = colR;
	out.g = colG;
	out.b = colB;

	return out;
}

void RainbowText::logic() //this one was hard as hell
{
	if (!initialized)
	{
		//std::cout << "ITC INTERNAL ERROR: RainbowText " << this->getString() << " was not initialized. Issues on GitHub.\n";
	}
	else
	{
		numOfChars = this->getString().getSize();
		if (comp.getString() != this->getString())	//if string gets changed
		{
			chars.clear();
			for (int i = 0; i < numOfChars; i++)	//push each character individually into the chars vector
				chars.push_back(sf::Text(this->getString().substring(i, 1), DefaultFont::getFont(), this->getCharacterSize()));
			comp = *this;
			numOfColors = 0;
			while (numOfColors < numOfChars)
				numOfColors += 18;
		}
		for (int i = 0; i < numOfChars; i++)	//most important attributes are here. if any of these get changed in text itself,
												//individual characters are updated with the new values. not performance hogging.
		{
			chars[i].setScale(this->getScale());
			chars[i].setRotation(this->getRotation());
			chars[i].setPosition(this->findCharacterPos(i));
			chars[i].setOutlineColor(this->getOutlineColor());
			chars[i].setOutlineThickness(this->getOutlineThickness());
		}
		if (!colorsInitialized)		//this could be done with fixed color rgb values but changeColor() may be useful for something else in the future
		{
			for (int i = 0; i < numOfColors; i++)
			{
				if (i == 0)
					colors.push_back(sf::Color(255, 0, 0, 255));
				else
				{
					colors.push_back(changeColor(colors[i - 1], 85));
				}
			}
			colorsInitialized = true;
		}
		if (magicSkipper == 1)
		{
			for (int i = 0; i < numOfChars; i++)	//this is where the magic starts. for every character, set a different color. see explanation below
			{
				if ((magicX + i) < numOfColors - 1)
				{
					chars[i].setFillColor(colors[magicX + i]);
				}
				else
				{
					chars[i].setFillColor(colors[magicY]);

					magicY++;
				}
			}
			magicY = 0;
			magicX++;
			if (magicX == numOfColors)
			{
				magicX = 0;
			}
			magicSkipper = 0;
		}
		else magicSkipper++;
	}

	//It is really difficult to explain this algorithm. If you want to understand it better, I suggest you start commenting out parts of code
	//to see exactly what does what. Here is the best explanation I could come up with:

	//	Let's say we have a word constited of 4 characters, which defaults to 18 different colors to shift through them.
	//
	//	first frame...
	//
	//	magicX = 0
	//	magicY = 0
	//
	//	chars[0] = colors[0 + 0]
	//	chars[1] = colors[0 + 1]
	//	chars[2] = colors[0 + 2]
	//	chars[3] = colors[0 + 3]
	//
	//	next frame...
	//
	//	magicX = 1
	//	magicY = 0
	//
	//	chars[0] = colors[1 + 0]
	//	chars[1] = colors[1 + 1]
	//	chars[2] = colors[1 + 2]
	//	chars[3] = colors[1 + 3]
	//
	//	13 frames later...
	//
	//	magicX = 15
	//	magicY = 0
	//
	//	chars[0] = colors[15 + 0]
	//	chars[1] = colors[15 + 1]
	//	chars[2] = colors[15 + 2]
	//	chars[3] = colors[15 + 3] ? Oops!Out of range.This breaks the if statement and we go to the magicY resort.
	//	chars[3] = colors[0] We are back at the beginning of the rainbow.
	//
	//	3 frames later...
	//
	//	magicX = 18
	//	magicY = 0
	//
	//	chars[0] = colors[18 + 0] - nope!we go to magicY again
	//	chars[0] = colors[0]
	//	chars[1] = colors[1] -	remember, magicY is incremented after each iteration in the for loop and gets reset to 0 after leaving it,
	//							but magicX is incremented outside of the for loop on every frame
	//	chars[2] = colors[2]
	//	chars[3] = colors[3]
	//
	//	Since magicX reached numOfColors(18), we reset it to 0 and start all over again.
}

void RainbowText::setLayer(Layer& _layer)
{
    layer = &_layer;
}

void RainbowText::render(sf::RenderWindow& window)
{
	if (layer != nullptr)
	{
		for (int i = 0; i < chars.size(); i++)
		{
			layer->render(window, chars.at(i));
		}
	}
}