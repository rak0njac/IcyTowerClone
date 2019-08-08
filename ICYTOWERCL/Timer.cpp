#include <Timer.h>
#include <Camera.h>
#include <iostream>

using namespace Timer;

int levels[6] { 1,2,4,6,9,11 };
bool started = false;
bool berserk = false;
bool shaking = false;

sf::Texture TxClock;
sf::Sprite Timer::SpClock;
sf::Texture TxClockHandle;
sf::Sprite Timer::SpClockHandle;

sf::Clock clox;
sf::Time timez;

void Timer::init() {
	TxClock.loadFromFile("..\\Assets\\Clock.png");
	SpClock.setTexture(TxClock);
	TxClockHandle.loadFromFile("..\\Assets\\ClockHandle.png");
	SpClockHandle.setTexture(TxClockHandle);
	SpClock.setOrigin(37, 47);
	SpClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
	SpClockHandle.setOrigin(37, 47);
	SpClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
}

void shakeAnim()
{
	static int count = 0;
	//std::cout << count << "\n";

	static bool xside = 1;
	static bool yside = 1;
	static float x = 0;
	static float y = 0;
	if (count < 400 && shaking)
	{
		if (xside)
		{
			if (x < 1)
				x++;
			else xside = 0;
		}
		else if (!xside)
		{ 
			if (x > -1)
				x--;
			else xside = 1;
		}
		if (yside)
		{
			if (y < 1)
				y+= 1.5f;
			else yside = 0;
		}
		else if (!yside)
		{
			if (y > -1)
				y-=1.5f;
			else yside = 1;
		}
		if (count % 2 == 0)
		{
			Timer::SpClockHandle.setPosition(const_timer_start_pos_x + x, const_timer_start_pos_y + y);
			if(count<350 || berserk)
				Timer::SpClock.setPosition(const_timer_start_pos_x + x, const_timer_start_pos_y + y);
		}
		count++;
	}
	else
	{
		count = 0;
		shaking = 0;
		if ((Timer::SpClock.getPosition().x != const_timer_start_pos_x && Timer::SpClock.getPosition().y != const_timer_start_pos_y) || 
			(Timer::SpClockHandle.getPosition().x != const_timer_start_pos_x && Timer::SpClockHandle.getPosition().y != const_timer_start_pos_y))
		{
			Timer::SpClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
			Timer::SpClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
		}
	}
}


void Timer::doLogic()
{
	static int i = 0;
	if (started)
	{
		if (!berserk)
		{
			timez = clox.getElapsedTime();
			SpClockHandle.setRotation(timez.asSeconds() * 12);
			//std::cout << timez.asSeconds() << "\n";
			if (timez.asSeconds() > 30.0f)
			{
				shaking = true;
				if (i < 4)
					i++;
				else
				{
					berserk = true;
					i = 5;
				}
				Camera::setCamLevel(levels[i]);
				clox.restart();
			}
		}
		else
		{
			SpClockHandle.rotate(-3);
			shaking = true;
		}
		shakeAnim();
	}
	else
	{
		Camera::setCamLevel(0);
		static float rot = SpClockHandle.getRotation();
		//started = false;
		SpClockHandle.setRotation(rot);
	}
}

bool Timer::getStarted() { return started; }

void Timer::setStarted(bool start)
{
	if (start)
	{
		started = start;
		Camera::setCamLevel(1);
		clox.restart();
	}
	else started = false;
}