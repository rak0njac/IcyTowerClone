#include "RainbowEngine.h"
#include <Font.h>
#include <iostream>

RainbowEngine::RainbowEngine(sf::Text& text)
{
	colorsInitialized = false;
	charsInitialized = false;
	//comp = text;
	numOfColors = 18;
	numOfChars = text.getString().getSize();
	this->text = &text;
	skipper = 0;
	x = 0;
	y = 0;
}

sf::Color RainbowEngine::changeColor(const sf::Color& color, const int delta)
{
	int colX = color.r;
	int colY = color.g;
	int colZ = color.b;

	if (color.r == 255 && color.g < 255 && color.b == 0)
		colY += delta;
	else if (color.r > 0 && color.g == 255 && color.b == 0)
		colX -= delta;
	else if (color.r == 0 && color.g == 255 && color.b < 255)
		colZ += delta;
	else if (color.r == 0 && color.g > 0 && color.b == 255)
		colY -= delta;
	else if (color.r < 255 && color.g == 0 && color.b == 255)
		colX += delta;
	else if (color.r == 255 && color.g == 0 && color.b > 0)
		colZ -= delta;

	if (colX > 255)
		colX = 255;
	if (colY > 255)
		colY = 255;
	if (colZ > 255)
		colZ = 255;
	if (colX < 0)
		colX = 0;
	if (colY < 0)
		colY = 0;
	if (colZ < 0)
		colZ = 0;

	//std::cout << "ColX: " << colX << "\nColY: " << colY << "\nColZ: " << colZ << "\n\n";
	//std::cout << "col:" << col << "\n";

	sf::Color out;
	out.r = colX;
	out.g = colY;
	out.b = colZ;

	return out;
}

void RainbowEngine::textMagic(sf::RenderWindow& window) //This one took 8 continuous hours of tinkering before it
{																		//finally worked properly so u are required to appreciate it

	//if (charsInitialized)// && (text->getString() != comp.getString()))
	//{
	//	charsInitialized = false;
	//	numOfChars = text->getString().getSize();
	//}
	////else charsInitialized = true;
	//if (!charsInitialized)
	//{
	if (skipper == 1)
	{
		numOfChars = text->getString().getSize();
		chars.clear();
		for (int i = 0; i < numOfChars; i++)
		{
			chars.push_back(sf::Text(text->getString().substring(i, 1), Font::getFont(), text->getCharacterSize()));
			chars[i].setScale(text->getScale());
			chars[i].setRotation(text->getRotation());
			chars[i].setPosition(text->findCharacterPos(i));
			chars[i].setOutlineColor(text->getOutlineColor());
			chars[i].setOutlineThickness(text->getOutlineThickness());
		}
		comp = *text;
		charsInitialized = true;
	}

	//}
	if (!colorsInitialized)
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


	if (skipper == 1)
	{
		for (int i = 0; i < numOfChars; i++)
		{
			if ((x + i) > numOfColors - 1)
			{
				chars[i].setFillColor(colors[y]);
				y++;
			}
			else
			{
				chars[i].setFillColor(colors[x + i]);
			}
		}
		y = 0;
		x++;
		if (x > numOfColors - 1)
		{
			x = 0;
		}
		skipper = 0;

	}
	else skipper++;

	if (1)//skipper == 1)
	{
		for (sf::Text& ch : chars)
		{
			window.draw(ch);
		}

	}
}