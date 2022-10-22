#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <PlatformEngine.h>
#include <Camera.h>
#include <Animation.h>
#include <Timer.h>
#include <Score.h>
#include <EyeCandyEngine.h>
#include <string>
#include <iostream>
#include <GameOver.h>
#include <PitchedSound.h>
#include <Consts.h>

class Player
{
private:
	float internalPosX;
	float internalPosY;

	bool onGround;
	Platform* curPlatform;
	EyeCandyEngine eceCombo;
	int curLevel;
	int levelMilestone;
	bool milestoneMode;
	sf::Image cjImg;
	sf::Texture cjTx;
	sf::Sprite cjSp;
	sf::SoundBuffer soundJumpLo;
	sf::SoundBuffer soundJumpMid;
	sf::SoundBuffer soundJumpHi;
	sf::SoundBuffer soundEdge;
	sf::SoundBuffer soundFalling;
	sf::SoundBuffer soundWazup;
	sf::SoundBuffer soundYo;
	static PitchedSound cjSound;

	sf::SoundBuffer soundMilestone;
	sf::Sound cjSoundMilestone;

	short side;
	short jumpStrenght;
	bool accelerating;
	float xSpeed;
	float ySpeed;
	float deltaSpeed;

	int checkBoundaries();
	void collide();
	void checkCollision();
	void milestoneReward();

	void animationAndSound();
	void move();
	void jump();

	void checkMilestone();
	void checkTimer();
	void checkMove();
	void checkJump();
	void checkCam();
	void checkCandy();
	void checkGameOver();
public:
	EyeCandyEngine eceMilestone;

	static void stopScreaming();
	void init();
	void logic();
	void render(sf::RenderWindow& window);
	void reset();
	sf::Drawable& getDrawable();
};