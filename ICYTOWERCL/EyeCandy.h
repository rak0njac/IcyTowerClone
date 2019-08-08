#pragma once
#include <SFML/Graphics.hpp>
const float const_eyecandy_gravity = 0.05f;
class EyeCandy
{
private:
	int step;

	int startPosX;
	int startPosY;
	float xSpeed;
	float ySpeed;
	sf::ConvexShape candy;

	void changeColor();
public:
	EyeCandy(float &posX, float &posY);

	sf::ConvexShape& getDrawable();
	float getPosY();

	void doLogic();
};