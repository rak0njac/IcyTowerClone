#include <Camera.h>

float camSpeed;
int	camLevel;

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
}

void Camera::stop()
{
	camSpeed = 0;
	camLevel = 0;
}