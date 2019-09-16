#include <Player.h>
#include <Game.h>

void Player::init()
{
	onGround = true;								//colliding
	curPlatform = &PlatformLayer::arrPlatform[0];
	curLevel = 1;									//platform which the player is standing on currently
	levelMilestone = 50;
	jumpStrenght = 0;								//depends on xSpeed, used to determine ySpeed, animation, and sound
	xSpeed = 0;
	ySpeed = 0;
	accelerating = false;
	deltaSpeed = 0;
	side = 0;

	cjImg.loadFromFile("..\\Assets\\harold.bmp");
	cjImg.createMaskFromColor(sf::Color(153, 20, 145, 255));
	cjTx.loadFromImage(cjImg);
	cjSp.setTexture(cjTx);
	cjSp.setOrigin(14, 35);
	cjSp.setPosition(const_player_start_pos_x, const_player_start_pos_y);

	//maybe make these as enum...
	soundEdge.loadFromFile("..\\Assets\\Sounds\\edge.ogg");
	soundJumpLo.loadFromFile("..\\Assets\\Sounds\\jump_lo.ogg");
	soundJumpMid.loadFromFile("..\\Assets\\Sounds\\jump_mid.ogg");
	soundJumpHi.loadFromFile("..\\Assets\\Sounds\\jump_hi.ogg");
	soundWazup.loadFromFile("..\\Assets\\Sounds\\wazup.ogg");
	soundYo.loadFromFile("..\\Assets\\Sounds\\yo.ogg");
	soundFalling.loadFromFile("..\\Assets\\Sounds\\falling.ogg");

	soundMilestone.loadFromFile("..\\Assets\\Sounds\\alright.ogg");
	cjSoundMilestone.setBuffer(soundMilestone);

	cjSound.setBuffer(soundYo);
	cjSound.play();
}


//Player::Player(std::string filename, int startPosX)		//for possible multiplayer in the future?
//{
//	onGround = true;
//	curPlatform = &PlatformLayer::arrPlatform[0];
//	curLevel = 1;
//	levelMilestone = 50;
//	jumpStrenght = 0;
//	xSpeed = 0;
//	ySpeed = 0;
//	accelerating = false;
//	deltaSpeed = 0;
//	side = 0;
//
//	cjImg.loadFromFile(filename);
//	cjImg.createMaskFromColor(sf::Color(153, 20, 145, 255));
//	cjTx.loadFromImage(cjImg);
//	cjSp.setTexture(cjTx);
//	cjSp.setOrigin(14, 35);
//	cjSp.setPosition(startPosX, const_player_start_pos_y);
//}

int Player::checkBoundaries()
{
	if (cjSp.getPosition().x >= const_left_bound && cjSp.getPosition().x <= const_right_bound)
		return 0;
	else if (cjSp.getPosition().x < const_left_bound)
		return const_left_bound;
	else return const_right_bound;
}

void Player::milestoneReward()
{
	cjSoundMilestone.play();
	eceMilestone.addCandy(320, 480, 320, 4, -7, 100);
	levelMilestone += 50;
}

void Player::collide()
{
	static float dist;
	if (jumpStrenght == 3)
	{
		dist = const_dist_between_platforms - 8;	//adjust the collision box due to rotation animation texture being higher by 8 pixels than normal
													//jump texture...and rotation animation is used only when jumpStrenght == 3
	}
	else dist = const_dist_between_platforms;

	if (cjSp.getPosition().y > const_dist_between_platforms * -1 * curLevel + const_player_start_pos_y + dist) // -1 is for UP on y axis, const_player_start_pos_y is because player doesn't start on pos 0, and dist is for fine tuning
	{
		for (Platform& p : PlatformLayer::arrPlatform)
		{
			if (p.getFloor() == curLevel &&	
				cjSp.getPosition().x >= p.startSp.getPosition().x - 12.5f && // rework when tilemap
				cjSp.getPosition().x <= p.endSp.getPosition().x + 14 + 12.5f) // CONST_END_TILE_WIDTH = 14
			{
				jumpStrenght = 0;
				ySpeed = 0;
				cjSp.setOrigin(14, 35);
				cjSp.setRotation(0);
				cjSp.setPosition(cjSp.getPosition().x, const_player_start_pos_y - const_dist_between_platforms * (curLevel - 1)); //collision itself can be a few pixels off on y axis so this sets the player's y position precisely where it needs to be
				onGround = true;
				curPlatform = &p;
				Score::changeScore((curLevel-1) * 10);
				if (curLevel >= levelMilestone)
				{
					milestoneReward();
				}
			}
		}
	}
}

void Player::checkCollision()	//checks on every frame if the player is still on previously collided platform
{
	if  (onGround && 
		!(cjSp.getPosition().x >= curPlatform->startSp.getPosition().x - 12.5f &&
		cjSp.getPosition().x <= curPlatform->endSp.getPosition().x + 14 + 12.5f)) 
	{
		jumpStrenght = 0;
		onGround = false;
	}
}

void Player::animationAndSound(PlatformLayer& pl)
{
	static int i = 0;
	static int j = 0;

	if (!onGround)																		//JUMPING
	{
		if (jumpStrenght != 3)
		{
			if (xSpeed > 0)
			{
				cjSp.setScale(side, 1);
				if (ySpeed < -1)
					cjSp.setTextureRect(Animation::cjAnimJump1);
				else if (ySpeed < 1)
					cjSp.setTextureRect(Animation::cjAnimJump2);
				else cjSp.setTextureRect(Animation::cjAnimJump3);
			}
			else
			{
				cjSp.setOrigin(14, 43);	//cjAnimJump is 8 pixels higher than regular textures so the y origin is 8 pixels higher too so the player doesn't clip through ground
				cjSp.setTextureRect(Animation::cjAnimJump);
			}
		}
		else
		{
			cjSp.setOrigin(21, 35);
			cjSp.rotate(6);
			cjSp.setTextureRect(Animation::cjAnimRotate);
		}
	}
	else if (cjSp.getPosition().x < const_left_bound + 1)								//HIT LEFT BOUND
	{
		cjSp.setScale(1, 1);
		cjSp.setTextureRect(Animation::cjAnimWalk1);
	}
	else if (cjSp.getPosition().x > const_right_bound - 1)								//HIT RIGHT BOUND
	{
		cjSp.setScale(-1, 1);
		cjSp.setTextureRect(Animation::cjAnimWalk1);
	}
	else if (xSpeed > 0 && !checkBoundaries())											//MOVING
	{
		cjSp.setScale(side, 1);
		i = 0;
		if (j < 20)
			cjSp.setTextureRect(Animation::cjAnimWalk1);
		else if (j < 100)
			cjSp.setTextureRect(Animation::cjAnimWalk2);
		else if (j < 150)
			cjSp.setTextureRect(Animation::cjAnimWalk3);
		else if (j < 200)
			cjSp.setTextureRect(Animation::cjAnimWalk4);
		else j = 0;
		j += xSpeed;
	}
	else if (cjSp.getPosition().x >= curPlatform->startSp.getPosition().x - 14 &&		//ON LEFT EDGE
		cjSp.getPosition().x <= curPlatform->startSp.getPosition().x + 12.5f)
	{
		if (cjSound.getStatus() != sf::Sound::SoundSource::Status::Playing)
		{
			cjSound.setBuffer(soundEdge);
			static int j = 30;
			if (j == 30)
			{
				cjSound.playPitched();
				j = 0;
			}
			j++;
		}
		cjSp.setScale(-1, 1);
		if (j < 15)
			cjSp.setTextureRect(Animation::cjAnimEdge1);
		else if (j < 30)
			cjSp.setTextureRect(Animation::cjAnimEdge2);
		else j = 0;
		j++;
	}
	else if (cjSp.getPosition().x >= curPlatform->endSp.getPosition().x &&					//ON RIGHT EDGE
		cjSp.getPosition().x <= curPlatform->endSp.getPosition().x + 14*2)
	{
		if (cjSound.getStatus() != sf::Sound::SoundSource::Status::Playing)
		{
			cjSound.setBuffer(soundEdge);
			static int j = 30;
			if (j == 30)
			{
				cjSound.playPitched();
				j = 0;
			}
			j++;
		}
		cjSp.setScale(1, 1);
		if (j < 15)
			cjSp.setTextureRect(Animation::cjAnimEdge1);
		else if (j < 30)
			cjSp.setTextureRect(Animation::cjAnimEdge2);
		else j = 0;
		j++;
	}
	else if (Camera::getCamLevel() > 0 && cjSp.getPosition().y > pl.getViewCenter() + const_chock_anim_trigger_bound) //CHOCK
	{
		cjSp.setTextureRect(Animation::cjAnimChock);
	}
	else																					//IDLE
	{
		j = 0;
		if (i < 25)
			cjSp.setTextureRect(Animation::cjAnimIdle1);
		else if (i < 50)
			cjSp.setTextureRect(Animation::cjAnimIdle2);
		else if (i < 75)
			cjSp.setTextureRect(Animation::cjAnimIdle1);
		else if (i < 100)
			cjSp.setTextureRect(Animation::cjAnimIdle3);
		else i = 0;
		i++;
	}
}

void Player::move()
{
	if (!checkBoundaries())
	{
		if (accelerating && xSpeed < const_player_xspeed_max) //accelerate
		{
			xSpeed += deltaSpeed;
		}
		else if (xSpeed - deltaSpeed < 0) //stop
		{
			xSpeed = 0;
		}
		else xSpeed -= deltaSpeed; //slow down
		cjSp.move(side * xSpeed, 0);
	}
	else
	{
		cjSp.setPosition(checkBoundaries(), cjSp.getPosition().y);
		side *= -1;
	}
}

void Player::jump()
{
	cjSp.move(0, ySpeed);
	if (ySpeed < const_player_yspeed_max)
		ySpeed += const_player_gravity;
	if (ySpeed > 0.0f)
		collide();
}

void Player::checkJump()		//WIP
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		onGround = false;
		if (xSpeed > 5.9f)
		{
			ySpeed = xSpeed * -1.25 - 7.0f; //CONST_XSPEED_JUMP_HIGH_FACTOR
			jumpStrenght = 3;
			cjSp.move(0, -8);	//since the rotation animation texture is 8 pixels higher, immediately move the player up 8 pixels so it doesn't look like
								//he is intersecting the ground when the animation kicks in. it couldn't be done by changing the y origin because the rotation
								//animation depends on origin being 35(standard).
			cjSound.setBuffer(soundJumpHi);
			cjSound.playPitched();
		}
		else if (xSpeed > 2.9f)
		{
			ySpeed = xSpeed * -0.55 - 7.0f; //CONST_XSPEED_JUMP_LOW_FACTOR
			jumpStrenght = 2;
			cjSound.setBuffer(soundJumpMid);
			cjSound.playPitched();
		}
		else
		{
			ySpeed = -7.0f;
			jumpStrenght = 1;
			cjSound.setBuffer(soundJumpLo);
			cjSound.playPitched();
		}
	}
	else if (!onGround)
	{
		jump();
	}
	curLevel = (cjSp.getPosition().y - const_player_start_pos_y) / const_dist_between_platforms * -1 + 1; //updated on every frame, brains of collision detection
}

void Player::checkMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (xSpeed > 0 && side == 1)
		{
			accelerating = false;
			deltaSpeed = const_player_slowdown_delta;
			move();
		}
		else
		{
			side = -1;
			accelerating = true;
			deltaSpeed = const_player_accelerate_delta;
			move();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (xSpeed > 0 && side == -1)
		{
			accelerating = false;
			deltaSpeed = const_player_slowdown_delta;
			move();
		}
		else
		{
			side = 1;
			accelerating = true;
			deltaSpeed = const_player_accelerate_delta;
			move();
		}
	}
	else
	{
		if (xSpeed > 0)
		{
			accelerating = false;
			deltaSpeed = const_player_friction_delta;
			move();
		}
		else side = 0;
	}
}

void Player::checkCam(PlatformLayer& pl)	//called on every frame
{
	if ((cjSp.getPosition().y  < pl.getViewCenter() - const_cam_catchup_top_bound))	//first and topmost section of the camera, used for fast catching up to speeding player
	{
		if (Camera::getCamSpeed() < const_cam_catchup_top_max_speed)
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_top_delta_speed * ySpeed * -1);
		else Camera::setCamSpeed(const_cam_catchup_top_max_speed);
	}
	else if (cjSp.getPosition().y < pl.getViewCenter() - const_cam_catchup_bottom_bound && ySpeed < 0) //second, middle section of the camera, used for fine tuning 
	{
		if (Camera::getCamSpeed() < const_cam_catchup_bottom_max_speed)
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_bottom_delta_speed * ySpeed * -1);
		else Camera::setCamSpeed(const_cam_catchup_bottom_max_speed);
	}
	else if (Camera::getCamSpeed() > Camera::getCamLevel()) //ensures smooth slowdown of camera after it's done relating to player
	{
		Camera::setCamSpeed(Camera::getCamSpeed() - Camera::getCamSpeed() * const_cam_catchup_slowdown_delta_speed);
	}
	else
	{
		Camera::setCamSpeed(Camera::getCamLevel());
	}
}

void Player::checkGameOver(PlatformLayer& pl)
{
	if (cjSp.getPosition().y > pl.getViewCenter() + 240 && !GameOver::isGameOver())
	{
		onGround = false;	//make the player fall down, sometimes the downmost platform is not deleted as soon as off screen

		cjSound.setBuffer(soundFalling);
		cjSound.setPitch(1);
		cjSound.play();

		GameOver::stopGame();
	}
}

void Player::checkCandy(sf::RenderWindow& window, PlatformLayer& pl)
{
	if (jumpStrenght == 3 && Score::isComboMode()) 
	{
		eceCombo.addCandy(cjSp.getPosition().x, cjSp.getPosition().y, 2);
	}
	eceCombo.doLogic(window, pl);
	eceMilestone.doLogic(window, Game::layerHud);
}

void Player::checkTimer()	//checks if the bound to start the timer is broken by the player
{
	if (!Timer::getStarted() && cjSp.getPosition().y < const_timer_start_bound && !GameOver::isGameOver())
		Timer::setStarted(true);
}

void Player::doLogic(sf::RenderWindow& window, PlatformLayer& pl)
{
	checkJump();
	checkMove();
	checkCollision();
	checkTimer();
	checkCam(pl);
	checkGameOver(pl);
	checkCandy(window, pl);
	animationAndSound(pl);
}

void Player::render(sf::RenderWindow& window, PlatformLayer& pl)
{
	pl.render(window, cjSp);
}

void Player::reset()
{
	onGround = true;
	curPlatform = &PlatformLayer::arrPlatform[0];
	curLevel = 1;
	levelMilestone = 50;
	jumpStrenght = 0;
	xSpeed = 0;
	ySpeed = 0;
	accelerating = false;
	deltaSpeed = 0;
	side = 0;

	cjSp.setOrigin(14, 35);
	cjSp.setPosition(const_player_start_pos_x, const_player_start_pos_y);
	cjSp.setRotation(0);

	eceCombo.reset();
	eceMilestone.reset();

	cjSound.setBuffer(soundYo);
	cjSound.play();
}