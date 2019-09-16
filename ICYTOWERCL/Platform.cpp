#include <iostream>
#include <random>
#include "Platform.h"
#include <Font.h>
#include <string>



Platform::Platform(int flr)
{
	startTx.loadFromFile("..\\Assets\\IceA.png");	//make it static
	middleTx.loadFromFile("..\\Assets\\Ice.png");
	endTx.loadFromFile("..\\Assets\\IceZ.png");
	floor = flr;
	position = generatePos();
	length = generateLen();
	startSp.setTexture(startTx);
	middleSp.setTexture(middleTx);
	endSp.setTexture(endTx);
	startSp.setOrigin(0, -508);
	startSp.setPosition(position, floor * const_dist_between_platforms * -1);				// get the start texture ready to draw with the first piece of	
	middleSp.setPosition(position + 25, floor * const_dist_between_platforms * -1);		// the middle texture just right to it ready to be repeated
	endSp.setOrigin(0, -508);													// and finally add end texture
	endSp.setPosition(position + 25 + length * 16, floor * const_dist_between_platforms * -1);
	//std::cout << length << "\n";
}

int Platform::generatePos()
{
	if (floor != 1 && floor % 50 != 0)
	{
		std::random_device rd;
		std::mt19937 rand(rd());
		std::uniform_int_distribution<> pos(75, 445);
		return pos(rand);
	}
	else return 50;
}

int Platform::generateLen()
{
	if (floor != 1 && floor % 50 != 0)
	{
		std::random_device rd;
		std::mt19937 rand(rd());

		if (position <= 315)
		{
			std::uniform_int_distribution<> len(5, 13); //13
			return len(rand);
		}
		else if (position > 315)					// basically, if the starting drawing position reaches a point where a platform
		{											// might overlap a wall if too long, we need to precisely control its possible length.
			int temp = position;					// each middle texture is 16px long so we increment i until we reach the overlapping point
			for (int i = 5; i <= 13; i++)	
			{
				temp += 16;
				if (temp > 445)
				{
					std::uniform_int_distribution<> len(5, i);
					//std::cout << "i = " << i;
					return len(rand);
				}
			}
		}
	}
	
	else return 32;
}

void Platform::regenerate()
{
	floor += 7;
	position = generatePos();
	length = generateLen();
	startSp.setPosition(position, floor * const_dist_between_platforms * -1);
	middleSp.setPosition(position + 25, floor * const_dist_between_platforms * -1);
	endSp.setPosition(position + 25 + length * 16, floor * const_dist_between_platforms * -1);
	if (floor % 10 == 0)
	{
		floorText.setString(std::to_string(floor));
		floorText.setFont(DefaultFont::getFont());
		floorText.setCharacterSize(30);
		floorText.setOrigin(floorText.getLocalBounds().width*0.5, floorText.getLocalBounds().height*0.5);
		floorText.setScale(0.5, 0.5);
		floorText.setPosition((endSp.getPosition().x + 14) - ((endSp.getPosition().x + 14) - startSp.getPosition().x) * 0.5f, 
			middleSp.getPosition().y + 14 + 508);
		floorText.setOutlineThickness(2);
		floorText.setOutlineColor(sf::Color::Black);
		floorText.setFillColor(sf::Color::White);
	}
}

int Platform::getFloor()
{
	return floor;
}

void Platform::reset(int flr)
{
	floor = flr - 7;
	regenerate();
}

void Platform::render(sf::RenderWindow& window)
{
	window.draw(startSp);
	for (int i = 0; i < length; i++)
	{
		middleSp.setOrigin(i * -16, -508);									// so just repeat it to the right
		window.draw(middleSp);
	}
	window.draw(endSp);
	//if (floorText.getCharacterSize() == 20)
		window.draw(floorText);
}