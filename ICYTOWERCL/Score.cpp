#include <Score.h>
#include <string.h>
#include <iostream>
#include <RainbowEngine.h>
#include <GameOver.h>
#include <EyeCandyEngine.h>
#include <Game.h>

int playerPos;	//used to calculate if the player has jumped two or more platforms in order to enter combo mode

int timesJumped;	//it is not a combo if the player doesn't jump at least twice
bool comboMode;
bool rewardMode;
bool stopMode;
bool rewardReset;
bool rewardAnimReset;

int rewardIndex;
float rewardSize;

int score;	//total score
int comboScore;		//current combo session score
int comboScoreTotal;	//score accumulated from all combo sessions
int bestCombo;

sf::Text textScore("SCORE: 0", Font::getFont(), 60);

sf::Text textConstFloors("floors", Font::getFont(), 20);
RainbowEngine re1("floors", Font::getFont(), 20);						//(textConstFloors);
sf::Text textComboFloors("", Font::getFont(), 30);
sf::Text textComboReward("", Font::getFont(), 140);
RainbowEngine re2("QWERTYUIOPASDFGHJKLZXCVBNM!", Font::getFont(), 140);


sf::Texture txComboMeter;
sf::Sprite spComboMeter;
sf::Texture txComboMeterBar;
sf::Sprite spComboMeterBar;

int comboBarHeight;

sf::ConvexShape star;

sf::Color color(255, 0, 0, 255);

EyeCandyEngine ece;



using namespace Score;

enum Reward
{
	Good,
	Sweet,
	Great,
	Super,
	Wow,
	Amazing,
	Extreme,
	Fantastic,
	Splendid,
	NoWay,
	RewardCount
};

sf::SoundBuffer soundBuffer[Reward::RewardCount];
sf::Sound sound;

void Score::init()
{
	playerPos = 0;

	timesJumped = 0;
	comboMode = false;
	rewardMode = false;
	rewardReset = false;
	rewardAnimReset = true;

	score = 0;
	comboScore = 0;
	comboScoreTotal = 0;
	bestCombo = 0;

	comboBarHeight = 0;

	//////
	textScore.setPosition(10, 440);
	textScore.setScale(0.5, 0.5);
	textScore.setOutlineThickness(6);
	textScore.setOutlineColor(sf::Color(1, 26, 51, 255));
	//textScore.setOrigin(textScore.getLocalBounds().width*0.5, textScore.getLocalBounds().height*0.5);

	txComboMeter.loadFromFile("..\\Assets\\ComboMeter.png");
	txComboMeterBar.loadFromFile("..\\Assets\\ComboMeterBar.png");
	spComboMeter.setTexture(txComboMeter);
	spComboMeterBar.setTexture(txComboMeterBar);

	spComboMeter.setPosition(20, 100);

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

	re1.setOutlineThickness(1);
	re1.setOutlineColor(sf::Color(1, 26, 51, 255));

	re2.setPosition(320, 290);
	re2.setScale(0.1f, 0.1f);
	re2.setOutlineThickness(7);
	re2.setOutlineColor(sf::Color(1, 26, 51, 255));

	soundBuffer[Reward::Good].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\good.ogg");
	soundBuffer[Reward::Sweet].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\sweet.ogg");
	soundBuffer[Reward::Great].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\great.ogg");
	soundBuffer[Reward::Super].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\super.ogg");
	soundBuffer[Reward::Wow].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\wow.ogg");
	soundBuffer[Reward::Amazing].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\amazing.ogg");
	soundBuffer[Reward::Extreme].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\extreme.ogg");
	soundBuffer[Reward::Fantastic].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\fantastic.ogg");
	soundBuffer[Reward::Splendid].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\splendid.ogg");
	soundBuffer[Reward::NoWay].loadFromFile("..\\Assets\\Sounds\\combo_rewards\\noway.ogg");
}

void changeColor()
{
	textScore.setFillColor(color);

	if (comboMode)
	{
		star.setFillColor(sf::Color(color.g, color.r, color.b, 255));
		textComboFloors.setFillColor(sf::Color(color.b, color.g, color.r, 255));
		color = RainbowEngine::changeColor(color, 51);
	}
	else
	{
		color = RainbowEngine::changeColor(color, 5);
	}
}

std::string getRewardString(int rewardIndex)
{
	if (rewardIndex == Reward::Good)
		return "GOOD!";
	if (rewardIndex == Reward::Sweet)
		return "SWEET!";
	if (rewardIndex == Reward::Great)
		return "GREAT!";
	if (rewardIndex == Reward::Super)
		return "SUPER!";
	if (rewardIndex == Reward::Wow)
		return "WOW!";
	if (rewardIndex == Reward::Amazing)
		return "AMAZING!";
	if (rewardIndex == Reward::Extreme)
		return "EXTREME!";
	if (rewardIndex == Reward::Fantastic)
		return "FANTASTIC!";
	if (rewardIndex == Reward::Splendid)
		return "SPLENDID!";
	if (rewardIndex == Reward::NoWay)
		return "NO WAY!";
}


void rewardLogic()
{
	static int phase = 0;
	static int step = 0;

	if (rewardAnimReset)
	{
		phase = 0;
		rewardAnimReset = false;
	}

	if (phase == 0)
	{
		if (comboScore > bestCombo)
			bestCombo = comboScore;
		if (comboScore >= 25)
		{
			ece.addCandy(320, 290, comboScore, 2, comboScore*0.5);
		}
		re2.setScale(0.05f, 0.05f);
		re2.setRotation(0);
		comboScore = 0;
		timesJumped = 0;
		step = 0;
		re2.setString(getRewardString(rewardIndex));
		sound.setBuffer(soundBuffer[rewardIndex]);
		sound.play();
		phase = 1;
	}

	else if (phase == 1)		//animation
	{
		if (step<75)//textComboReward.getScale().x < rewardSize)
		{	
			re2.scale(rewardSize, rewardSize);
			re2.rotate(4.8);
			re2.setOrigin(re2.getLocalBounds().width * 0.5f, re2.getLocalBounds().height * 0.5f);


			step++;
		}
		else phase = 2;
	}
	else if (phase == 2)		//show reward for some time after animation finishes
	{
		if (step < 150)
		{
			step++;
		}
		else phase = 3;
	}
	else if (phase == 3)
	{
		if (re2.getScale().x > 0.05f)
		{
			re2.scale(0.85f, 0.85f);
			re2.rotate(-18);
			re2.setOrigin(re2.getLocalBounds().width * 0.5f, re2.getLocalBounds().height * 0.5f);
		}
		else phase = 4;
	}
	else
	{
		phase = 0;
		rewardMode = false;
		rewardReset = false;
	}

}

void handleRewards()
{
	if (comboScore < 7)
	{
		rewardIndex = 0;
		rewardSize = 1.028f;
	}
		//reward("GOOD!", 50);
	else if (comboScore < 15)
	{
		rewardIndex = 1;
		rewardSize = 1.03f;
	}
	//	reward("SWEET!", 60);
	else if (comboScore < 25)
	{
		rewardIndex = 2;
		rewardSize = 1.032f;
	}
	//	reward("GREAT!", 70);
	else if (comboScore < 35)
	{
		rewardIndex = 3;
		rewardSize = 1.034f;
	}
	//	reward("SUPER!", 80);
	else if (comboScore < 50)
	{
		rewardIndex = 4;
		rewardSize = 1.04f;
	}
	//	reward("WOW!", 90);
	else if (comboScore < 70)
	{
		rewardIndex = 5;
		rewardSize = 1.0375f;
	}
	//	reward("AMAZING!", 100);
	else if (comboScore < 100)
	{
		rewardIndex = 6;
		rewardSize = 1.0375f;
	}
	//	reward("EXTREME!", 110);
	else if (comboScore < 140)
	{
		rewardIndex = 7;
		rewardSize = 1.0375f;
	}
	//	reward("FANTASTIC!", 120);
	else if (comboScore < 200)
	{
		rewardIndex = 8;
		rewardSize = 1.038f;
	}
	//	reward("SPLENDID!", 130);
	else 
	{
		rewardIndex = 9;
		rewardSize = 1.0425;
	}//reward("NO WAY!", 140);
}

void startCombo()
{
	comboMode = true;
	spComboMeterBar.setPosition(31, 119);
	comboBarHeight = 100;

	star.setPosition(0, 215);
	//textConstFloors.setPosition(6, 245);
	re1.setPosition(6, 245);
}

void updateComboScore(int score)
{
	timesJumped++;
	comboScore += (score) * 0.1f;
	textComboFloors.setString(std::to_string(comboScore));
	textComboFloors.setPosition(38 - textComboFloors.getLocalBounds().width * 0.5f, 215); //center the text
}

void updateScore()
{
	score = playerPos + comboScoreTotal;
	textScore.setString("SCORE: " + std::to_string(score));
	//std::cout << comboScoreTotal;
}

void endCombo()		//will be called once if no reward. called lots of times if reward. maybe fix this up hmm
{
	comboBarHeight = 0;
	spComboMeterBar.setTextureRect(sf::IntRect(11, 19, 16, comboBarHeight));
	if (comboScore >= 4 && timesJumped >= 2 && !rewardMode)	//prevent total combo score from multiplying on each call if reward is being presented
	{
		comboScoreTotal += comboScore * comboScore;
		rewardMode = true;
		handleRewards();	//call every frame until the reward presentation finishes

	}
	if (rewardMode)	
	{
	}
	else		//immediately (or finally) finish the combo logic
	{
		comboScore = 0;
		timesJumped = 0;
		updateScore();
		comboMode = false;
	}
}



void comboLogic()
{
	if (comboBarHeight > 0)
	{
		static bool skipper = 0;	//to prevent the bar from draining too quickly, drain it 1 px every 2 frames
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
		endCombo();
	}
}

void Score::changeScore(int i)
{
	if (playerPos + 20 <= i)	//jumped two or more floors - start combo
	{
		if (rewardMode && !rewardReset)
		{
			comboScore = 0;
			timesJumped = 0;
			rewardReset = true;
		}
		startCombo();
	}

	if (comboMode)
	{
		if(playerPos + 20 <= i)
			updateComboScore(i - playerPos);
		else if (playerPos == i) {}	//jumped on the same floor he was already on - do nothing
		else endCombo();			//jumped one floor up, or any number of floors down - end the combo
	}
	
	score = i + comboScoreTotal;
	textScore.setString("SCORE: " + std::to_string(score));
	playerPos = i;
}

sf::Vector2i Score::stop()
{
	static int phase = 0;
	static int i = 0;
	static sf::Text textScoreTemp;
	static sf::Vector2f deltaScale;
	static sf::Vector2f deltaPos;
	static sf::Vector2i values;

	//std::cout << phase << "\n";

	if (!GameOver::isGameOver())
	{
		i = 0;
		phase = 0;
		stopMode = false;
	}

	if (phase == 0)
	{
		comboMode = false;
		//
		//rewardMode = false;
		stopMode = true;
		phase = 1;
		textScoreTemp = textScore;
		textScoreTemp.setScale(0.63, 0.63);
		textScoreTemp.setOrigin(textScore.getLocalBounds().width * 0.5, textScore.getLocalBounds().height * 0.5);
		textScoreTemp.setPosition(320, 290);
		deltaScale = textScoreTemp.getScale() - textScore.getScale();
		deltaPos.x = textScoreTemp.getGlobalBounds().left - textScore.getGlobalBounds().left;
		deltaPos.y = textScoreTemp.getGlobalBounds().top - textScore.getGlobalBounds().top;
	}

	else if (phase == 1)
	{
		if (i < 75)
		{
			textScore.setScale(textScore.getScale().x + deltaScale.x / 75, textScore.getScale().y + deltaScale.y / 75);
			textScore.move(deltaPos.x / 75, deltaPos.y / 75);
			i++;
			//std::cout << textScore.getScale().x << "\n";
		}
		else phase = 2;
	}
	else if (phase == 2)
	{
		textScore = textScoreTemp;
	}
	values.x = playerPos * 0.1;
	values.y = bestCombo;
	return values;
}


void Score::doLogic()
{
	if (comboMode)
	{
		comboLogic();
	}

	if (rewardMode)
	{
		rewardLogic();
	}
	
	if (stopMode)
	{
		stop();
	}

}

void Score::render(Layer& layer, sf::RenderWindow& window)
{
	static bool init = false;
	if (!init)
	{
		re1.textMagic(window, layer);
		re2.textMagic(window, layer);
		init = true;
	}

	changeColor();
	layer.render(window, textScore);
	layer.render(window, spComboMeter);
	if (comboMode)
	{
		layer.render(window, spComboMeterBar);
		layer.render(window, star);
		layer.render(window, textComboFloors);
		re1.textMagic(window, layer);
	}

	if (rewardMode)
	{
		ece.doLogic(window, layer);
		re2.textMagic(window, layer);
	}
}

bool Score::isComboMode() { return comboMode; }

void Score::reset()
{
	playerPos = 0;

	timesJumped = 0;
	//comboMode = false;
	rewardMode = false;
	stopMode = false;
	rewardReset = false;
	rewardAnimReset = true;

	score = 0;
	comboScore = 0;
	comboScoreTotal = 0;
	bestCombo = 0;

	comboBarHeight = 0;

	textScore.setOrigin(0, 0);
	textScore.setPosition(10, 440);
	textScore.setScale(0.5, 0.5);
	textScore.setString("SCORE: " + std::to_string(score));
}