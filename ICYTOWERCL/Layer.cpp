#include <Layer.h>

Layer::Layer()
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	camPosY = 0;
	speedDelta = 1;
	step = const_cam_start_step;
	conststep = step;
}

Layer::Layer(float speedDelta)
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	camPosY = 0;
	step = const_cam_start_step - const_cam_start_step / speedDelta;
	this->speedDelta = speedDelta;
	conststep = step;
}

void Layer::logic()
{
	float camSpeed = Camera::getCamSpeed();
	view.reset(sf::FloatRect(0, camPosY, 640, 480));
	camPosY -= const_cam_speed_delta * camSpeed * speedDelta;
	step -= camSpeed;
	if (step <= 0) 
	{
		camPosY = 0;
		if (speedDelta != 1) {
			step = const_cam_start_step - const_cam_start_step / speedDelta;
		}
		else step = const_cam_start_step;
	}
}

void Layer::render(sf::RenderWindow& window, sf::Drawable& drawable)
{
	window.setView(view);
	window.draw(drawable);
}

float Layer::getViewCenter()
{
	return view.getCenter().y;
}

void Layer::reset()
{
	view.reset(sf::FloatRect(0, 0, 640, 480));
	camPosY = 0;
	step = conststep;
}