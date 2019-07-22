#include <Layer.h>

Layer::Layer(float step)
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	CamY = 0;
	speedFactor = 1;
	this->step = step;
	this->num = num;
}

Layer::Layer(float step, float speedFactor)
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	CamY = 0;
	this->step = step - step / speedFactor;
	this->speedFactor = speedFactor;
	this->num = num;
}

void Layer::move(float camSpeedFactor, int camSpeed, int startStep)
{
	view.reset(sf::FloatRect(0, CamY, 640, 480));
	CamY -= camSpeedFactor * camSpeed * speedFactor;
	step -= camSpeed;
	if (step <= 0) 
	{
		CamY = 0;
		if (speedFactor != 1) {
			step = startStep - startStep / speedFactor;
		}
		else step = startStep;
	}
}

void Layer::render(sf::RenderWindow& window, sf::Sprite& sprite)
{
	window.setView(view);
	window.draw(sprite);
}