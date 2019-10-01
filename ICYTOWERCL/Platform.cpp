#include "Platform.h"

sf::Image Platform::imgPlatform;
sf::Texture Platform::txPlatform;

Platform::Platform(int flr)
{
	spPlatform.setTexture(txPlatform);
	floor = flr;
	position = generatePos();
	length = generateLen();
	spPlatform.setPosition(position, floor * const_dist_between_platforms * -1 + 508);
	vect = FloorTypes::getIntRects(FloorTypes::Type::Snow);
	startPos = position;
	endPos = position + vect[0].width + length * vect[1].width + vect[2].width;
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

	else return 36;
}

void Platform::regenerate()
{
	floor += 7;
	position = generatePos();
	length = generateLen();
	spPlatform.setPosition(position, floor * const_dist_between_platforms * -1 + 508);

	int floorType = -1;
	if (floor < 50)
		floorType = FloorTypes::Type::Snow;
	else if (floor < 100)
		floorType = FloorTypes::Type::Ice;
	else if (floor < 150)
		floorType = FloorTypes::Type::Wood;
	else if (floor < 200)
		floorType = FloorTypes::Type::Blue;
	else if (floor < 250)
		floorType = FloorTypes::Type::PinkGoo;
	else if (floor < 300)
		floorType = FloorTypes::Type::Bone;
	else if (floor < 350)
		floorType = FloorTypes::Type::Liana;
	else if (floor < 400)
		floorType = FloorTypes::Type::Mario;
	else if (floor < 450)
		floorType = FloorTypes::Type::Cloud;
	else if (floor < 500)
		floorType = FloorTypes::Type::Rainbow;

	vect = FloorTypes::getIntRects(floorType);

	startPos = position;
	endPos = position + vect[0].width + length * vect[1].width + vect[2].width;

	if (floor % 10 == 0)
	{
		textFloor.setString(std::to_string(floor));
		textFloor.setFont(DefaultFont::getFont());
		textFloor.setCharacterSize(const_text_size_small);
		textFloor.setOutlineThickness(const_text_outline_small);
		textFloor.setScale(0.75, 0.75);
		textFloor.setOutlineColor(sf::Color::Black);
		textFloor.setFillColor(sf::Color::White);
		textFloor.setOrigin(textFloor.getLocalBounds().width / 2, textFloor.getLocalBounds().height / 2);
		if (floor % 50 != 0)
			textFloor.setPosition((startPos + endPos) / 2, spPlatform.getPosition().y + vect[0].height / 2);
		else textFloor.setPosition(320, spPlatform.getPosition().y + vect[0].height / 2);
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

void Platform::init()
{
	imgPlatform.loadFromFile("..\\Assets\\floors.bmp");
	imgPlatform.createMaskFromColor(sf::Color(153, 20, 145, 255));
	txPlatform.loadFromImage(imgPlatform);
}

void Platform::render(sf::RenderWindow& window)
{
	spPlatform.setTextureRect(vect[0]);
	window.draw(spPlatform);
	spPlatform.move(vect[0].width, 0);
	spPlatform.setTextureRect(vect[1]);
	for (int i = 0; i < length; i++)
	{
		window.draw(spPlatform);
		spPlatform.move(vect[1].width, 0);
	}
	//spPlatform.move(vect[1].width, 0);
	spPlatform.setTextureRect(vect[2]);
	window.draw(spPlatform);
	textFloor.setPosition((int)textFloor.getPosition().x, (int)textFloor.getPosition().y);
	window.draw(textFloor);

	spPlatform.setPosition(startPos, spPlatform.getPosition().y);
}