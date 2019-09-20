#include "EyeCandyEngine.h"

EyeCandyEngine::EyeCandyEngine()
{
	layer = nullptr;
}

//is there a way to make EyeCandyEngine inherit these parameters automatically from all EyeCandy constructors, so I don't
//have to add a new function here whenever I add a new EyeCandy constructor?

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

void EyeCandyEngine::setLayer(Layer& _layer)
{
	layer = &_layer;
}

void EyeCandyEngine::render(sf::RenderWindow& window)	//todo: separate logic and render, needed for Score::rewardLogic() optimization
{
	if (layer != nullptr)
	{
		for (int i = 0; i < engine.size(); i++)
		{
			EyeCandy& ecref = engine.at(i);
			ecref.logic();
			layer->render(window, ecref.getDrawable());
			if (ecref.getPosY() > layer->getViewCenter() + 240 && engine.size() > 0)
			{
				engine.erase(engine.begin() + i);
			}
		}
	}
}

void EyeCandyEngine::reset()
{
	engine.clear();
}