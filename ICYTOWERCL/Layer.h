#pragma once
#include <SFML/Graphics.hpp>
#include <Camera.h>

class Layer
{
protected:
	float camY;
	float speedDelta;
	float step;
	sf::View view;
public:
	virtual void move();
	void render(sf::RenderWindow& window, sf::Drawable& sprite);
	Layer();
	Layer(float speedDelta);
};

