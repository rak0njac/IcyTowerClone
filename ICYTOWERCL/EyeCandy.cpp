#include "EyeCandy.h"
#include <random>
#include <iostream>

EyeCandy::EyeCandy(const float &posX, const float &posY)
{
	step = 5;									//used for changing colors. cannot use static in changeColor() because of wierd bug (some stars keep being white)
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(-3, 3);
	std::uniform_real_distribution<> randDir(-2, 2);
	std::uniform_real_distribution<> randGrav(0.05, 0.1);
	startPosX = posX + randPos(rand);
	startPosY = posY;
	xSpeed = randDir(rand);
	ySpeed = -2;
	gravity = randGrav(rand);

	candy.setPointCount(10);
	candy.setPoint(0, sf::Vector2f(5, 0));   //
	candy.setPoint(1, sf::Vector2f(6, 3));
	candy.setPoint(2, sf::Vector2f(10, 3));
	candy.setPoint(3, sf::Vector2f(8, 6));
	candy.setPoint(4, sf::Vector2f(9, 9));
	candy.setPoint(5, sf::Vector2f(5, 8));
	candy.setPoint(6, sf::Vector2f(1, 9));
	candy.setPoint(7, sf::Vector2f(2, 6)); 	 //
	candy.setPoint(8, sf::Vector2f(0, 3));	 //
	candy.setPoint(9, sf::Vector2f(4, 3));	 //

	candy.setOrigin(5, 4);
	candy.setPosition(startPosX, startPosY);
}

EyeCandy::EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir)
{
	step = 5;									//used for changing colors. cannot use static in changeColor() because of wierd bug (some stars keep being white)
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(_randPos*-1, _randPos);
	std::uniform_real_distribution<> randDir(_randDir * -1, _randDir);
	std::uniform_real_distribution<> randGrav(0.05, 0.1);
	startPosX = posX + randPos(rand);
	startPosY = posY;
	xSpeed = randDir(rand);
	ySpeed = -2;
	gravity = randGrav(rand);

	candy.setPointCount(10);
	candy.setPoint(0, sf::Vector2f(5, 0));   //
	candy.setPoint(1, sf::Vector2f(6, 3));
	candy.setPoint(2, sf::Vector2f(10, 3));
	candy.setPoint(3, sf::Vector2f(8, 6));
	candy.setPoint(4, sf::Vector2f(9, 9));
	candy.setPoint(5, sf::Vector2f(5, 8));
	candy.setPoint(6, sf::Vector2f(1, 9));
	candy.setPoint(7, sf::Vector2f(2, 6)); 	 //
	candy.setPoint(8, sf::Vector2f(0, 3));	 //
	candy.setPoint(9, sf::Vector2f(4, 3));	 //

	candy.setOrigin(5, 4);
	candy.setPosition(startPosX, startPosY);
}

EyeCandy::EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed)
{
	step = 5;									
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> randPos(_randPos * -1, _randPos);
	std::uniform_real_distribution<> randDir(_randDir * -1, _randDir);
	std::uniform_real_distribution<> randGrav(0.05, 0.1);
	startPosX = posX + randPos(rand);
	startPosY = posY;
	xSpeed = randDir(rand);
	ySpeed = _ySpeed;
	gravity = randGrav(rand);

	candy.setPointCount(10);
	candy.setPoint(0, sf::Vector2f(5, 0));   //
	candy.setPoint(1, sf::Vector2f(6, 3));
	candy.setPoint(2, sf::Vector2f(10, 3));
	candy.setPoint(3, sf::Vector2f(8, 6));
	candy.setPoint(4, sf::Vector2f(9, 9));
	candy.setPoint(5, sf::Vector2f(5, 8));
	candy.setPoint(6, sf::Vector2f(1, 9));
	candy.setPoint(7, sf::Vector2f(2, 6)); 	 //
	candy.setPoint(8, sf::Vector2f(0, 3));	 //
	candy.setPoint(9, sf::Vector2f(4, 3));	 //

	candy.setOrigin(5, 4);
	candy.setPosition(startPosX, startPosY);
}

const sf::ConvexShape& EyeCandy::getDrawable()
{
	return candy;
}

void EyeCandy::changeColor()
{
	static sf::Color col[6]{ sf::Color::Blue, sf::Color::Cyan , sf::Color::Green, sf::Color::Magenta, sf::Color::Red, sf::Color::Yellow };
	
	static std::random_device rd;
	static std::mt19937 rand(rd());
	static std::uniform_int_distribution<> randCol(0, 5);

	if (step < 5)
		step++;
	else
	{
		candy.setFillColor(col[randCol(rand)]);
		step = 0;
	}
}

void EyeCandy::doLogic()
{
	changeColor();
	candy.move(xSpeed, ySpeed);
	//candy.rotate(60);

	if (ySpeed < 5)
		ySpeed += gravity;//const_eyecandy_gravity;

	if (xSpeed < -0.5)
		xSpeed += 0.02;
	else if (xSpeed > 0.5)
		xSpeed -= 0.02;

	//std::cout << ySpeed << "\n";
}

float EyeCandy::getPosY()
{
	return candy.getPosition().y;
}