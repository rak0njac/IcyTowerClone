#pragma once
#include <SFML/Graphics.hpp>
#include <Camera.h>
#include <Consts.h>

//Layers are not used to determine drawing order - that can be done individually in the game loop itself, rather they are used
//for handling logic of moving the sprites along with the camera by rendering them on a per-object sf::View with each layer
//having its own speed factor simulating depth in the game graphics.

class Layer
{
protected:
	float camPosY;
	float speedDelta;	//determines how many times faster does the layer move than a layer with a speedDelta of 1.
						//setting it to 0 makes the layer indepentent of camera movement(used for HUD)
	float step;
	float constStep;
	sf::View view;
public:
	virtual void logic();
	float getViewCenter();	//used for garbage collection for moving objects to calculate whether they have left the screen.
	void render(sf::RenderWindow& window, sf::Drawable& sprite);
	virtual void reset();
	Layer();
	Layer(float speedDelta);
};
