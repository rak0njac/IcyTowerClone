#include "EyeCandyEngine.h"
#include <iostream>

EyeCandyEngine::EyeCandyEngine()
{
	//a legend is born
}

void EyeCandyEngine::addCandy(float posX, float posY)
{
	engine.push_back(EyeCandy(posX, posY));
}

void EyeCandyEngine::doLogic(sf::RenderWindow &window, PlatformLayer& pl)
{
	for (int i = 0; i < engine.size(); i++)
	{
		EyeCandy& eck = engine.at(i);
		eck.doLogic();
		window.draw(eck.getDrawable());
		if (eck.getPosY() > pl.getViewCenter() + 240 && engine.size() > 0)
		{
				engine.erase(engine.begin()+i);
		}
	}
	//std::cout << engine.size() << "\n";
}