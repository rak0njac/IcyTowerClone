#include <Score.h>

//Scoring sequence goes like this: changeScore() is called each time the player collides a platform from the Player.cpp collide(). 
//a check is performed to see whether or not the player has jumped more than one platform, if so, it activates the combo mode.
//in combo mode, the combo bar is drained as a matter of time the player has to extend his combo. if the player jumps more than one platform,
//the combo bar is reset and extended, but if the player jumps only one platform up or any number of platforms down, endCombo() is called directly from changeScore()
//elsewhere it is called by comboLogic() when the combo bar is drained. when endCombo() is called, a check is performed to see whether the combo made by the player
//meets the rule for combo score calculation - needs to jump at least twice. handleRewards() is called to set the combo reward index and font size.
//the game then goes into reward mode, a reward animation sequence starts in rewardLogic(), along with the star and number of floors to the left of the
//screen (just like in combo mode).

int playerPos;	//used to calculate if the player has jumped two or more platforms in order to enter combo mode

int timesJumped;	//it is not a combo if the player doesn't jump at least twice
bool comboMode;
bool rewardMode;
bool stopMode;
bool rewardAnimReset;	//if the reward is still being displayed, but the player finishes a new combo for a new reward, used to interrupt the old reward

int rewardIndex;
float rewardSize;	//size in graphical matter

int score;	//total score
int comboScore;		//current combo session score
int comboScoreTotal;	//score accumulated from all combo sessions
int bestCombo;

sf::Text textScore("SCORE: 0", DefaultFont::getFont(), 40);

RainbowText rtFloors("FLOORS", DefaultFont::getFont(), const_text_size_small);		
sf::Text textNumOfFloors("", DefaultFont::getFont(), const_text_size_medium);
RainbowText rtReward("", DefaultFont::getFont(), const_text_size_large);

sf::Texture txComboMeter;
sf::Sprite spComboMeter;
sf::Texture txComboMeterBar;
sf::Sprite spComboMeterBar;

int comboBarHeight;

sf::ConvexShape star;

sf::Color color(255, 0, 0, 255);

EyeCandyEngine ece;

static Layer& curLayer = Game::Layers::HUD;

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
std::string rewardStrings[Reward::RewardCount];
sf::Sound sound;

void Score::init()
{
	playerPos = 0;

	timesJumped = 0;
	comboMode = false;
	rewardMode = false;
	rewardAnimReset = true;

	score = 0;
	comboScore = 0;
	comboScoreTotal = 0;
	bestCombo = 0;

	comboBarHeight = 0;

	textScore.setPosition(10, 440);
	textScore.setScale(0.75, 0.75);
	textScore.setOutlineThickness(const_text_outline_medium);
	textScore.setOutlineColor(const_color_outline);

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
	star.setOutlineColor(const_color_outline);

	star.setPosition(0, 215);
	rtFloors.setPosition(6, 245);

	textNumOfFloors.setOutlineThickness(const_text_outline_medium);
	textNumOfFloors.setOutlineColor(const_color_outline);
	textNumOfFloors.setPosition(42, 227);

	rtFloors.init();
	rtReward.init();

	rtFloors.setOutlineThickness(const_text_outline_small);
	rtFloors.setOutlineColor(const_color_outline);

	rtReward.setPosition(320, 290);		//set position here, it is not changed afterwards!
	rtReward.setOutlineThickness(const_text_outline_large);
	rtReward.setOutlineColor(const_color_outline);

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

	rewardStrings[Reward::Good] = "GOOD!";
	rewardStrings[Reward::Sweet] = "SWEET!";
	rewardStrings[Reward::Great] = "GREAT!";
	rewardStrings[Reward::Super] = "SUPER!";
	rewardStrings[Reward::Wow] = "WOW!";
	rewardStrings[Reward::Amazing] = "AMAZING!";
	rewardStrings[Reward::Extreme] = "EXTREME!";
	rewardStrings[Reward::Fantastic] = "FANTASTIC!";
	rewardStrings[Reward::Splendid] = "SPLENDID!";
	rewardStrings[Reward::NoWay] = "NO WAY!";

	//for some reason getLocalBounds() is extremely expensive, probably because it requests all the glyphs for the current string from the font
	//which would make it as expensive as draw(). But once the glyphs are in memory they are just reused whenever requested, so this way we request all
	//the glyphs at load time. If it wasn't for this then the game would stutter when the first combo reward in a game session was displayed.
	for (std::string s : rewardStrings)
	{
		rtReward.setString(s);
		rtReward.getLocalBounds();
	}
	rtFloors.getLocalBounds();

	ece.setLayer(curLayer);
	rtFloors.setLayer(curLayer);
	rtReward.setLayer(curLayer);
}

void changeColor()
{
	textScore.setFillColor(color);

	if (comboMode || rewardMode)
	{
		star.setFillColor(sf::Color(color.g, color.r, color.b, 255));
		textNumOfFloors.setFillColor(sf::Color(color.b, color.g, color.r, 255));
		color = RainbowText::changeColor(color, 51);
	}
	else
	{
		color = RainbowText::changeColor(color, 5);
	}
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

	if (phase == 0)		//init
	{
		rtReward.setScale(0.05f, 0.05f);
		rtReward.setRotation(0);
		step = 0;
		rtReward.setString(rewardStrings[rewardIndex]);
		sound.setBuffer(soundBuffer[rewardIndex]);
		sound.play();
		phase++;
	}

	else if (phase == 1)		//animation 1st sequence
	{
		if (step < 75)
		{
			rtReward.scale(rewardSize, rewardSize);
			rtReward.rotate(4.8);
			rtReward.setOrigin(rtReward.getLocalBounds().width / 2, rtReward.getLocalBounds().height / 2);

			step++;
		}
		else phase++;
	}
	else if (phase == 2)		//show reward for some time after animation finishes
	{
		if (step < 150)
		{
			step++;
		}
		else phase++;
	}
	else if (phase == 3)	//animation last sequence
	{
		if (rtReward.getScale().x > 0.05f)
		{
			rtReward.scale(0.85f, 0.85f);
			rtReward.rotate(-18);
			rtReward.setOrigin(rtReward.getLocalBounds().width / 2, rtReward.getLocalBounds().height / 2);
		}
		else phase++;
	}
	else if (phase == 4)
	{
		phase = 0;
		rewardMode = false;
	}
	rtFloors.logic();
	rtReward.logic();
	ece.logic();
}

void handleRewards()
{
	if (comboScore < 7)
	{
		rewardIndex = Reward::Good;
		rewardSize = 1.028f;
	}
	else if (comboScore < 15)
	{
		rewardIndex = Reward::Sweet;
		rewardSize = 1.03f;
	}
	else if (comboScore < 25)
	{
		rewardIndex = Reward::Great;
		rewardSize = 1.032f;
	}
	else if (comboScore < 35)
	{
		rewardIndex = Reward::Super;
		rewardSize = 1.034f;
	}
	else if (comboScore < 50)
	{
		rewardIndex = Reward::Wow;
		rewardSize = 1.04f;
	}
	else if (comboScore < 70)
	{
		rewardIndex = Reward::Amazing;
		rewardSize = 1.0375f;
	}
	else if (comboScore < 100)
	{
		rewardIndex = Reward::Extreme;
		rewardSize = 1.0375f;
	}
	else if (comboScore < 140)
	{
		rewardIndex = Reward::Fantastic;
		rewardSize = 1.0375f;
	}
	else if (comboScore < 200)
	{
		rewardIndex = Reward::Splendid;
		rewardSize = 1.038f;
	}
	else 
	{
		rewardIndex = Reward::NoWay;
		rewardSize = 1.0425;
	}
}

void startCombo()
{
	comboMode = true;
	spComboMeterBar.setPosition(31, 119);
	comboBarHeight = 100;
}

void updateComboScore(int score)
{
	timesJumped++;
	comboScore += score / 10;
	textNumOfFloors.setString(std::to_string(comboScore));
	textNumOfFloors.setOrigin(textNumOfFloors.getLocalBounds().width / 2, textNumOfFloors.getLocalBounds().height / 2);
}

void endCombo()
{
	comboBarHeight = 0;
	spComboMeterBar.setTextureRect(sf::IntRect(11, 19, 16, comboBarHeight));
	if (timesJumped >= 2)	//reward applicable
	{
		comboScoreTotal += comboScore * comboScore;
		if (rewardMode)
			rewardAnimReset = true;
		else rewardMode = true;

		//these need to be called before comboScore is set to 0
		handleRewards();	
		if (comboScore > bestCombo)
			bestCombo = comboScore;
		ece.addCandy(320, 290, comboScore, 2, comboScore / 2);
	}
	comboScore = 0;
	timesJumped = 0;
	comboMode = false;
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
		rtFloors.logic();
	}
	else
	{
		endCombo();
	}
}

void Score::changeScore(int platform)
{
	if (playerPos + 20 <= platform)	//jumped two or more floors - start combo
	{
		startCombo();
	}

	if (comboMode)
	{
		if (playerPos + 20 <= platform)
			updateComboScore(platform - playerPos);
		else if (playerPos != platform) //if on the same floor he was already on - do nothing
			endCombo(); //jumped one floor up, or any number of floors down - end the combo
	}
	
	score = platform + comboScoreTotal;
	textScore.setString("SCORE: " + std::to_string(score));
	playerPos = platform;
}

sf::Vector2i Score::stop()
{
	stopMode = true;
	sf::Vector2i values;
	values.x = playerPos / 10;
	values.y = bestCombo;
	return values;
}

void stopLogic()	//animation where the score goes from the bottom left corner to the center of the screen
{
	static int phase = 0;
	static int step = 0;

	static sf::Text textScoreTemp;
	static sf::Vector2f deltaScale;
	static sf::Vector2f deltaPos;

	if (!GameOver::isGameOver())	//check on each frame if the game is no longer in game over state then reset all these statics
	{
		step = 0;
		phase = 0;
		stopMode = false;
	}
	else 
	{
		if (phase == 0)
		{
			comboMode = false;
			//stopMode = true;

			//calculate delta for every frame between current size/pos and desired size/pos
			textScoreTemp = textScore;
			textScoreTemp.setScale(1, 1);
			textScoreTemp.setOrigin(textScore.getLocalBounds().width * 0.5, textScore.getLocalBounds().height * 0.5);
			textScoreTemp.setPosition(320, 290);
			deltaScale = textScoreTemp.getScale() - textScore.getScale();
			deltaPos.x = textScoreTemp.getGlobalBounds().left - textScore.getGlobalBounds().left;
			deltaPos.y = textScoreTemp.getGlobalBounds().top - textScore.getGlobalBounds().top;

			phase++;
		}

		else if (phase == 1)
		{
			const int numOfFrames = 75;
			if (step < numOfFrames)
			{
				textScore.setScale(textScore.getScale().x + deltaScale.x / numOfFrames, textScore.getScale().y + deltaScale.y / numOfFrames);
				textScore.move(deltaPos.x / numOfFrames, deltaPos.y / numOfFrames);
				step++;
			}
			else phase++;
		}
		else if (phase == 2)
		{
			textScore = textScoreTemp;
		}
	}


}


void Score::logic()
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
		stopLogic();
	}
	changeColor();
}

void Score::render(sf::RenderWindow& window)
{
	curLayer.render(window, textScore);
	curLayer.render(window, spComboMeter);
	if (comboMode || rewardMode)
	{
		curLayer.render(window, spComboMeterBar);
		curLayer.render(window, star);
		curLayer.render(window, textNumOfFloors);
		rtFloors.render(window);
	}

	if (rewardMode)
	{
		ece.render(window, false);
		rtReward.render(window);
	}
}

bool Score::isComboMode() { return comboMode; }

void Score::reset()
{
	playerPos = 0;

	timesJumped = 0;
	comboMode = false;
	rewardMode = false;
	//stopMode = false;			//this is set to false on reset in stopLogic()
	rewardAnimReset = true;

	score = 0;
	comboScore = 0;
	comboScoreTotal = 0;
	bestCombo = 0;

	comboBarHeight = 0;

	textScore.setOrigin(0, 0);
	textScore.setPosition(10, 440);
	textScore.setScale(0.75, 0.75);
	textScore.setString("SCORE: 0");
}