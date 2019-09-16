#pragma once
#include <SFML/Graphics.hpp>
const float const_eyecandy_gravity = 0.075f;
class EyeCandy
{
private:
	int colorChangeIndex;
	float gravity;
	int startPosX;
	int startPosY;
	float xSpeed;
	float ySpeed;
	sf::ConvexShape candy;

	void changeColor();
	void createStarShape();
public:
	EyeCandy(const float &posX, const float &posY);
	EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir);
	EyeCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed);

	sf::ConvexShape& getDrawable();
	float getPosY();

	void logic();
};