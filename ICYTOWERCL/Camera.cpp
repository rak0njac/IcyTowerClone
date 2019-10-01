#include <Camera.h>

float camSpeed;		//the number of pixels to move the camera
int	camLevel;		//game level - increases every time the clock rings, in normal occasions camSpeed = camLevel, when camera is catching up to the
					//player, camSpeed = camLevel + catching up float

int Camera::getCamLevel()
{
	return camLevel;
}
float Camera::getCamSpeed()
{
	return camSpeed;
}
void Camera::setCamLevel(int value)
{
	camLevel = value;
}
void Camera::setCamSpeed(float value)
{
	camSpeed = value;
	//std::cout << "CamSpeed is now: " << value << "\n";
}

void Camera::stop()
{
	camSpeed = 0;
	camLevel = 0;
}