#include <iostream>
#include <random>
#include "Platform.h"
#include "Camera.h"



Platform::Platform(int x)
{
	level = 1;
	startTx.loadFromFile("..\\Assets\\IceA.png");
	middleTx.loadFromFile("..\\Assets\\Ice.png");
	endTx.loadFromFile("..\\Assets\\IceZ.png");
	floor = x;
	position = generatePos();
	length = generateLen();
	startSp.setTexture(startTx);
	middleSp.setTexture(middleTx);
	endSp.setTexture(endTx);
	startSp.setOrigin(0, -508);
	startSp.setPosition(static_cast<float>(position), floor * yDistance * -1);				// get the start texture ready to draw with the first piece of	
	middleSp.setPosition(static_cast<float>(position) + 25, floor * yDistance * -1);		// the middle texture just right to it ready to be repeated
	endSp.setOrigin(0, -508);													// and finally add end texture
	endSp.setPosition(static_cast<float>(position) + 25 + length * 16, floor * yDistance * -1);
	//render();
}


Platform::~Platform()
{
	//delete this;
}

// Most of the numbers are pixel perfect calculations calculated by trial and error. This was done to
// provide better/best accuracy to the original game, the algorithms are not meant to be flexible.

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
			std::uniform_int_distribution<> len(5, 13);
			return len(rand);
		}
		else if (position > 315)					// basically, if the starting drawing position reaches a point where a platform
		{											// might overlap a wall if too long, we need to precisely control its possible length
			int temp = position;					// each middle texture is 16px long so we increment i until we reach the overlapping point
			for (int i = 5; i < 14; i++)
			{
				//std::cout << i << "\n";
				temp += 16;
				if (temp > 445)
				{
					temp = i;						// and in the end just using temp so as not to create additional variables
					break;
				}
			}
			std::uniform_int_distribution<> len(5, temp);
			return len(rand);
		}
	}
	
	else return 32;
}

void Platform::regenerate()
{
	floor += 7;
	position = generatePos();
	length = generateLen();
	startSp.setOrigin(0, -508);
	startSp.setPosition(static_cast<float>(position), floor * yDistance * -1);
	middleSp.setPosition(static_cast<float>(position) + 25, floor * yDistance * -1);
	endSp.setOrigin(length * -16, -508);									
	endSp.setPosition(static_cast<float>(position) + 25, floor * yDistance * -1);
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
	//window.display();
	//std::cout << "It works!";
}