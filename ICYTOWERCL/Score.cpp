#include <Score.h>
#include <string.h>
#include <iostream>

int Score::playerPos;

int Score::timesJumped;
bool Score::comboMode;
bool Score::comboStart;

int Score::score;
int Score::comboScore;
int Score::comboScoreTotal;

sf::Text Score::textScore("SCORE: 0", Font::getFont(), 30);

sf::Text Score::textConstFloors("floors", Font::getFont(), 20);
sf::Text Score::textComboFloors("", Font::getFont(), 30);

sf::Texture Score::txComboMeter;
sf::Sprite Score::spComboMeter;
sf::Texture Score::txComboMeterBar;
sf::Sprite Score::spComboMeterBar;

int Score::comboBarHeight;

sf::ConvexShape Score::star;

void Score::init()
{
	playerPos = 0;

	timesJumped = 0;
	comboMode = false;
	comboStart = true;

	score = 0;
	comboScore = 0;
	comboScoreTotal = 0;

	comboBarHeight = 0;

	//////
	textScore.setPosition(10, 440);
	textScore.setOutlineThickness(3);
	textScore.setOutlineColor(sf::Color(1, 26, 51, 255));

	txComboMeter.loadFromFile("..\\Assets\\ComboMeter.png");
	txComboMeterBar.loadFromFile("..\\Assets\\ComboMeterBar.png");
	spComboMeter.setTexture(txComboMeter);
	spComboMeterBar.setTexture(txComboMeterBar);

	spComboMeter.setPosition(20, 100);
	spComboMeterBar.setPosition(31, 119);

	star.setPointCount(16);
	star.setPoint(0, sf::Vector2f(41, 18));
	star.setPoint(1, sf::Vector2f(59, 4));
	star.setPoint(2, sf::Vector2f(51, 26));
	star.setPoint(3, sf::Vector2f(74, 32));
	star.setPoint(4, sf::Vector2f(57, 39));
	star.setPoint(5, sf::Vector2f(62, 55));
	star.setPoint(6, sf::Vector2f(45, 44));
	star.setPoint(7, sf::Vector2f(34, 63));
	star.setPoint(8, sf::Vector2f(30, 45));
	star.setPoint(9, sf::Vector2f(7, 53));
	star.setPoint(10, sf::Vector2f(22, 39));
	star.setPoint(11, sf::Vector2f(1, 32));
	star.setPoint(12, sf::Vector2f(18, 27));
	star.setPoint(13, sf::Vector2f(5, 12));
	star.setPoint(14, sf::Vector2f(23, 17));
	star.setPoint(15, sf::Vector2f(28, 1));

	star.setOutlineThickness(4);
	star.setOutlineColor(sf::Color(1, 26, 51, 255));
	textConstFloors.setOutlineThickness(1);
	textComboFloors.setOutlineThickness(3);
	textComboFloors.setOutlineColor(sf::Color(1, 26, 51, 255));
	textConstFloors.setOutlineColor(sf::Color(1, 26, 51, 255));
}

//void checkColor(int i)
//{
//	if (col != i)
//	{
//		x = 255;
//		y = 0;
//		z = 0;
//		col = i;
//	}
//}

void Score::changeColor()
{
	static int x = 255;
	static int y = 0;
	static int z = 0;
	static int col = 51;

	if(comboMode&&!comboStart)
	{
		x = 255;
		y = 0;
		z = 0;
		col = 51;
	}
	else if (!comboMode && comboStart)
	{
		x = 255;
		y = 0;
		z = 0;
		col = 5;
	}
	if (x == 255 && y < 255 && z == 0)
		y += col;
	else if (x > 0 && y == 255 && z == 0)
		x -= col;
	else if (x == 0 && y == 255 && z < 255)
		z += col;
	else if (x == 0 && y > 0 && z == 255)
		y -= col;
	else if (x < 255 && y == 0 && z == 255)
		x += col;
	else if (x == 255 && y == 0 && z > 0)
		z -= col;

	textScore.setFillColor(sf::Color(x, y, z, 255));
	star.setFillColor(sf::Color(x, y, z, 255));
	textConstFloors.setFillColor(sf::Color(y, x, z, 255));
	textComboFloors.setFillColor(sf::Color(z, x, y, 255));
}

void Score::combo()
{
	if (comboMode)
	{
		if (!comboStart)
		{
			star.setPosition(0, 215);
			textConstFloors.setPosition(6, 245);
			//checkColor(51);
			comboStart = true;
		}
		if (comboBarHeight > 0)
		{
			static bool skipper = 0;
			if (!skipper)
			{
				comboBarHeight--;
				spComboMeterBar.setTextureRect(sf::IntRect(11, 19, 16, comboBarHeight));
				spComboMeterBar.move(0, 1);
				skipper = 1;
			}
			else skipper = 0;
		}
		else
		{
			comboMode = false;
		}
	}
	else
	{
		if (comboStart)
		{
			star.setPosition(1337, 1337);
			textComboFloors.setPosition(1337, 1337);
			textConstFloors.setPosition(1337, 1337);
			//checkColor(5);
			if (comboScore >= 4 && timesJumped >= 2)
				comboScoreTotal += comboScore * comboScore;
			comboScore = 0;
			timesJumped = 0;
			changeScore(playerPos);
			comboBarHeight = 0;
			spComboMeterBar.setTextureRect(sf::IntRect(11, 19, 16, comboBarHeight));
			comboStart = false;
		}
	}
}

void Score::changeScore(int i)
{
	if (playerPos + 20 <= i)
	{
		comboMode = true;
		spComboMeterBar.setPosition(31, 119);
		comboBarHeight = 100;
	}
	else if (playerPos == i) {}
	else comboMode = false;
	if (comboMode)
	{
		timesJumped++;
		comboScore += (i - playerPos) * 0.1f;
		textComboFloors.setString(std::to_string(comboScore));
		textComboFloors.setPosition(38 - textComboFloors.getLocalBounds().width * 0.5f, 215);
	}
	score = i + comboScoreTotal;
	textScore.setString("SCORE: " + std::to_string(score));
	playerPos = i;
}

bool Score::isComboMode() { return comboMode; }

void Score::stop()
{
	textScore.setPosition(320 - textScore.getLocalBounds().width * 0.5f, 240 - textScore.getLocalBounds().height*0.5f);
	textScore.setCharacterSize(80);
}

void Score::doLogic()
{
	changeColor();
	combo();
	//std::cout << "Current combo score: " << comboScore << "\nTotal combo score: " << comboScoreTotal << "\nScore: " << score << "\n\n";
}

void Score::render(Layer& l, sf::RenderWindow& window)
{
	l.render(window, textScore);
	l.render(window, spComboMeter);
	l.render(window, spComboMeterBar);
	l.render(window, star);
	l.render(window, textComboFloors);
	l.render(window, textConstFloors);
}