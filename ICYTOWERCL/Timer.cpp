#include <Timer.h>
#include <Camera.h>
#include <iostream>
#include <GameOver.h>
#include <Font.h>
#include <RainbowEngine.h>
#include <SFML\Audio.hpp>
#include <Game.h>

using namespace Timer;

int levels[6] { 1,2,4,6,9,11 };
int i = 0;

bool started = false;
bool berserk = false;
bool shaking = false;
bool hurrying = false;

sf::Texture TxClock;
sf::Sprite Timer::SpClock;
sf::Texture TxClockHandle;
sf::Sprite Timer::SpClockHandle;

RainbowText textHurry("HURRY UP!", DefaultFont::getFont(), 160);
//RainbowEngine reHurry(textHurry);

sf::Clock clox;
sf::Time timez;

sf::SoundBuffer sb;
static sf::Sound sound;

Layer* curLayer;

void Timer::init() {
	TxClock.loadFromFile("..\\Assets\\Clock.png");
	SpClock.setTexture(TxClock);
	TxClockHandle.loadFromFile("..\\Assets\\ClockHandle.png");
	SpClockHandle.setTexture(TxClockHandle);
	SpClock.setOrigin(37, 47);
	SpClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
	SpClockHandle.setOrigin(37, 47);
	SpClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
	textHurry.setScale(0.5, 0.5);
	textHurry.setOutlineThickness(10);
	textHurry.setOutlineColor(sf::Color(1, 26, 51, 255));
	textHurry.setOrigin(textHurry.getLocalBounds().width * 0.5, textHurry.getLocalBounds().height * 0.5);
	textHurry.setPosition(320, 540);

	sb.loadFromFile("..\\Assets\\Sounds\\hurry.ogg");
	sound.setBuffer(sb);

	curLayer = &Game::Layers::layerHud;

	textHurry.init();
	textHurry.setLayer(*curLayer);
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
			else if(Timer::SpClock.getPosition().x != const_timer_start_pos_x && Timer::SpClock.getPosition().y != const_timer_start_pos_y)
				Timer::SpClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
		}
		count++;
	}
	else
	{
		count = 0;
		shaking = 0;
		if (Timer::SpClockHandle.getPosition().x != const_timer_start_pos_x && Timer::SpClockHandle.getPosition().y != const_timer_start_pos_y)
		{
			Timer::SpClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
		}
	}
}

void displayHurryUp()
{
	if (hurrying)
	{
		if (textHurry.getPosition().y > -80)
		{
			textHurry.move(0, -1);
			textHurry.textMagic();
		}
		else
		{
			textHurry.setPosition(320, 540);
			hurrying = false;
		}
	}
}


void Timer::logic()
{
	timez = clox.getElapsedTime();
	if (started)
	{
		if (!berserk)
		{
			SpClockHandle.setRotation(timez.asSeconds() * 12);
			//std::cout  << timez.asSeconds() << "\n";
			if (timez.asSeconds() > 30)
			{
				shaking = true;
				hurrying = true;
				sound.play();
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
		displayHurryUp();
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

void Timer::reset()
{
	i = 0;
	clox.restart();
	started = false;
	shaking = false;
	berserk = false;
	hurrying = false;
	SpClockHandle.setRotation(0);
	textHurry.setPosition(320, 540);
}

void Timer::render(sf::RenderWindow& window, int sprite)
{
	if (sprite == Sprites::Clock)
	{
		curLayer->render(window, SpClock);
		curLayer->render(window, SpClockHandle);
	}
	else if (sprite == Sprites::HurryUpText)
	{
		if(hurrying)
			textHurry.render(window);
	}
}