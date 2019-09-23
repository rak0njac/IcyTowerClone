#pragma once
#include <SFML\Graphics.hpp>
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


const float const_player_gravity = 0.225f;
const float const_player_start_pos_x = 180;
const float const_player_start_pos_y = 417;
const int const_left_bound = 87;
const int const_right_bound = 553;
const int const_chock_anim_trigger_bound = 140;
const float const_player_xspeed_max = 6;
const float const_player_yspeed_max = 6;
const float const_player_slowdown_delta = 0.75f;
const float const_player_accelerate_delta = 0.085f;
const float const_player_friction_delta = 0.14f;

class Player
{
private:
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
	PitchedSound cjSound;

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

	void init();
	void logic();
	void render(sf::RenderWindow& window);
	void reset();
	sf::Drawable& getDrawable();
};