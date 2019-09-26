#include <Timer.h>

static int levels[7] { 0,1,2,4,6,9,11 };
static int curLevel = 0;

static bool started = false;	//has the player advanced high enough so the timer can start counting & camera start moving?
static bool berserk = false;	//final level of the game, the clock handle rotates counter-clockwise and clock keeps shaking (used mostly for clockShakeAnim() )
static bool shaking = false;	//is the clock shaking?
static bool hurrying = false;	//is the hurry up text being displayed?

static sf::Texture txClock;
static sf::Sprite spClock;
static sf::Texture txClockHandle;
static sf::Sprite spClockHandle;

static RainbowText textHurry("HURRY UP!", DefaultFont::getFont(), const_text_size_large);

static sf::SoundBuffer sb;
static sf::Sound sound;

static Layer* curLayer;

void Timer::init() {
	txClock.loadFromFile("..\\Assets\\Clock.png");
	spClock.setTexture(txClock);
	txClockHandle.loadFromFile("..\\Assets\\ClockHandle.png");
	spClockHandle.setTexture(txClockHandle);
	spClock.setOrigin(37, 47);
	spClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
	spClockHandle.setOrigin(37, 47);
	spClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);

	textHurry.setOutlineThickness(const_text_outline_large);
	textHurry.setOutlineColor(sf::Color(1, 26, 51, 255));
	textHurry.setOrigin(textHurry.getLocalBounds().width / 2, textHurry.getLocalBounds().height / 2);
	textHurry.setPosition(320, 540);
	textHurry.setScale(0.6, 0.6);

	sb.loadFromFile("..\\Assets\\Sounds\\hurry.ogg");
	sound.setBuffer(sb);

	curLayer = &Game::Layers::HUD;

	textHurry.init();
	textHurry.setLayer(*curLayer);
}

void clockShakeAnim()
{
	static int step = 0;

	static bool xSide = 1;	//where is the clock going on the x axis (left or right)
	static bool ySide = 1;
	static float xPos = -1;	//clock position in pixels 
	static float yPos = -1;

	if (shaking && step < 400)
	{
		if (xSide)
		{
			if (xPos < 1)
				xPos++;
			else xSide = 0;
		}
		else
		{ 
			if (xPos > -1)
				xPos--;
			else xSide = 1;
		}
		if (ySide)
		{
			if (yPos < 1)
				yPos+= 1.5f;
			else ySide = 0;
		}
		else
		{
			if (yPos > -1)
				yPos-=1.5f;
			else ySide = 1;
		}
		if (step % 2 == 0)
		{
			spClockHandle.setPosition(const_timer_start_pos_x + xPos, const_timer_start_pos_y + yPos);

			if(step < 350 || berserk)	//the handle should shake a few more moments than the clock itself (nice for attention to detail lol)
				spClock.setPosition(const_timer_start_pos_x + xPos, const_timer_start_pos_y + yPos);
			else if(spClock.getPosition().x != const_timer_start_pos_x && spClock.getPosition().y != const_timer_start_pos_y)
				spClock.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
		}
		step++;
	}
	else
	{
		step = 0;
		shaking = false;
		if (spClockHandle.getPosition().x != const_timer_start_pos_x && spClockHandle.getPosition().y != const_timer_start_pos_y)
		{
			spClockHandle.setPosition(const_timer_start_pos_x, const_timer_start_pos_y);
		}
	}
}

void hurryUpAnim()
{
	if (hurrying)
	{
		if (textHurry.getPosition().y > -80)
		{
			textHurry.move(0, -1);
			textHurry.logic();
		}
		else
		{
			textHurry.setPosition(320, 540);
			hurrying = false;
		}
	}
}


void Timer::logic()		//todo fix readability
{
	static int phase = 0;
	if (phase == 0)
	{
		if (started)
		{
			curLevel = 1;
			Camera::setCamLevel(curLevel);
			clock.restart();
			phase++;
		}
	}
	time = clock.getElapsedTime();
	if (started)
	{
		if (phase == 1)
		{
			spClockHandle.setRotation(time.asSeconds() * 12);

			if (time.asSeconds() > 30)
			{
				shaking = true;
				hurrying = true;
				sound.play();

				if (curLevel < 5)
				{
					curLevel++;
					clock.restart();
					Camera::setCamLevel(curLevel);
				}
				else
				{
					Camera::setCamLevel(curLevel);
					phase++;
				}
			}
			clockShakeAnim();
			hurryUpAnim();
		}
		else if (phase == 2)
		{
			curLevel = 5;
			berserk = true;
			shaking = true;
			spClockHandle.rotate(-3);
			clockShakeAnim();
			hurryUpAnim();
		}
	}
	else if (phase != 0)
		phase = 0;
}

bool Timer::getStarted() { return started; }

void Timer::setStarted(bool start)
{
	started = start;
}

void Timer::reset()
{
	curLevel = 0;
	clock.restart();
	started = false;
	shaking = false;
	berserk = false;
	hurrying = false;
	spClockHandle.setRotation(0);
	textHurry.setPosition(320, 540);
}

void Timer::render(sf::RenderWindow& window, int sprite)
{
	if (sprite == Sprites::Clock)
	{
		curLayer->render(window, spClock);
		curLayer->render(window, spClockHandle);
	}
	else if (sprite == Sprites::HurryUpText)
	{
		if(hurrying)
			textHurry.render(window);
	}
}