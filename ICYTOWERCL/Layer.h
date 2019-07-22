#pragma once
#include <SFML/Graphics.hpp>
class Layer
{
protected:
	sf::View view;
	float CamY;
	float speedFactor;
	float step;
public:
	int num;
	virtual void move(float camSpeedFactor, int camSpeed, int startStep);
	void render(sf::RenderWindow& window, sf::Sprite& sprite);
	Layer(float step);
	Layer(float step, float speedFactor);
};

