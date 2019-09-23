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

void EyeCandyEngine::logic()
{
	for (EyeCandy& ec : engine)
	{
		ec.logic();
	}
}

void EyeCandyEngine::render(sf::RenderWindow& window, bool _reset)	//bool - when star goes off screen, delete it or reset?
{
	if (layer != nullptr)
	{
		for (int i = 0; i < engine.size(); i++)
		{
			EyeCandy& ec = engine.at(i);
			//ecref.logic();
			layer->render(window, ec.getDrawable());
			if (ec.getPosY() > layer->getViewCenter() + 240 && engine.size() > 0)
			{
				if (_reset)
					enginePassive.push_back(ec);
				engine.erase(engine.begin() + i);
			}
		}
	}
}

void EyeCandyEngine::resetCandy()
{
	for (EyeCandy& ec : enginePassive)
	{
		ec.reset();
	}
	engine = enginePassive;
	enginePassive.clear();
}

int EyeCandyEngine::getCount()
{
	return engine.size();
}

void EyeCandyEngine::reset()
{
	engine.clear();
}