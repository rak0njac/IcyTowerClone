#include "Layer.h"
#include <Player.h>
#include <Platform.h>
class PlatformLayer : Layer
{
private:
	//Platform arrPlatform[7]{ 1,2,3,4,5,6,7 };
public:
	static Platform arrPlatform[7];
	//void collide(sf::Sprite& player);
	void move(float camSpeedFactor, int camSpeed);
	void render(sf::RenderWindow& window);
	PlatformLayer(float step, float speedFactor) :Layer(step, speedFactor) {}
};