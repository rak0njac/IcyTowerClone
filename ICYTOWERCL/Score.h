#pragma once
#include <SFML/Graphics.hpp>
#include <Font.h>
#include <Layer.h>

class Score
{
private:
	static int playerPos;
	static int timesJumped;
	static bool comboMode;
	static bool comboStart;

	static int score;
	static int comboScore;
	static int comboScoreTotal;

	static sf::Text textScore;
	static sf::Texture txComboMeter;
	static sf::Texture txComboMeterBar;
	static sf::Sprite spComboMeter;
	static sf::Sprite spComboMeterBar;
	static sf::ConvexShape star;
	static sf::Text textConstFloors;
	static sf::Text textComboFloors;

	static int comboBarHeight;

	static void changeColor();
	static void combo();
public:
	static void changeScore(int i);
	static void init();
	static void doLogic();
	static void stop(); //
	static bool isComboMode();

	static void render(Layer& l, sf::RenderWindow& window);
};