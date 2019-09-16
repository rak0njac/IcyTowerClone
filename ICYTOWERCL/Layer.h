#pragma once
#include <SFML/Graphics.hpp>
#include <Camera.h>
#include <vector>

class Layer
{
protected:
	float camPosY;
	float speedDelta;
	float step;
	float conststep;
	sf::View view;
public:
	virtual void logic();
	float getViewCenter();
	void render(sf::RenderWindow& window, sf::Drawable& sprite);
	virtual void reset();
	Layer();
	Layer(float speedDelta);
};

