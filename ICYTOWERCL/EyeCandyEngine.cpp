#include "EyeCandyEngine.h"
#include <iostream>

EyeCandyEngine::EyeCandyEngine()
{
	//a legend is born
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, int count)
{
	for(int i=0; i<count;i++)
		engine.push_back(EyeCandy(posX, posY));
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, int count)
{
	for (int i = 0; i < count;i++)
		engine.push_back(EyeCandy(posX, posY, _randPos, _randDir));
}

void EyeCandyEngine::addCandy(const float& posX, const float& posY, const float& _randPos, const float& _randDir, const float& _ySpeed, int count)
{
	for (int i = 0; i < count;i++)
		engine.push_back(EyeCandy(posX, posY, _randPos, _randDir, _ySpeed));

}

void EyeCandyEngine::doLogic(sf::RenderWindow &window, Layer& pl)
{
	for (int i = 0; i < engine.size(); i++)
	{
		EyeCandy& eck = engine.at(i);
		eck.doLogic();
		//window.draw(eck.getDrawable());
		pl.render(window, eck.getDrawable());
		if (eck.getPosY() > pl.getViewCenter() + 240 && engine.size() > 0)
		{
				engine.erase(engine.begin()+i);
		}
	}
	//std::cout << engine.size() << "\n";
}

void EyeCandyEngine::reset()
{
	engine.clear();
}