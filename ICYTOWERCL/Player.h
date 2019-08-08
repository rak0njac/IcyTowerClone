#pragma once
#include <SFML\Graphics.hpp>
#include <PlatformLayer.h>
#include <Camera.h>
#include <Animation.h>
#include <Timer.h>
#include <Score.h>
#include <EyeCandyEngine.h>
#include <string>

const float const_player_gravity = 0.25f;
const float const_player_start_pos_x = 180;
const float const_player_start_pos_y = 417;
const int const_left_bound = 87;
const int const_right_bound = 553;
const int const_chock_anim_trigger_bound = 140;
const float const_player_xspeed_max = 6;
const float const_player_yspeed_max = 7;
const float const_player_slowdown_delta = 0.5f;
const float const_player_accelerate_delta = 0.085f;
const float const_player_friction_delta = 0.14f;

class Player
{
private:
	bool onGround;
	Platform* curPlatform;
	EyeCandyEngine ece;
	int level;
	sf::Image cjImg;
	sf::Texture cjTx;
	sf::Sprite cjSp;
	short side;
	short jumpStrenght;
	bool accelerating;
	float xSpeed;
	float ySpeed;
	float deltaSpeed;

	int checkBoundaries();
	void collide();
	void checkCollision();
	void animationAndSound(PlatformLayer& pl);
	void move();
	void jump();

	void checkMove();
	void checkJump();
	void checkCam(PlatformLayer& pl);
	void checkCandy(sf::RenderWindow& window, PlatformLayer& pl);
	void checkGameOver(PlatformLayer& pl);
public:
	Player();
	Player(std::string filename);
	void doLogic(sf::RenderWindow& window, PlatformLayer& pl);
	void render(sf::RenderWindow& window, PlatformLayer& pl);
};