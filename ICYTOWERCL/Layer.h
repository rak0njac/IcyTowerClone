#pragma once
#include <SFML/Graphics.hpp>
#include <Camera.h>

class Layer
{
protected:
	float camY;
	float speedDelta;
	float step;
	float conststep;
	sf::View view;
public:
	virtual void move();
	float getViewCenter();
	void render(sf::RenderWindow& window, const sf::Drawable& sprite);
	virtual void reset();
	Layer();
	Layer(float speedDelta);
};

