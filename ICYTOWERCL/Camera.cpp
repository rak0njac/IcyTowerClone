#include <Camera.h>

float Camera::camSpeed;
int	Camera::camLevel;

int& Camera::getCamLevel()
{
	return camLevel;
}
float& Camera::getCamSpeed()
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
}