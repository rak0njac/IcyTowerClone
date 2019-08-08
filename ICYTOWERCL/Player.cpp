#include <Player.h>

Player::Player()
{
	onGround = true;
	curPlatform = &PlatformLayer::arrPlatform[0];
	level = 1;
	jumpStrenght = 0;
	xSpeed = 0;
	ySpeed = 0;
	accelerating = false;
	deltaSpeed = 0;

	cjImg.loadFromFile("..\\Assets\\harold.bmp");
	cjImg.createMaskFromColor(sf::Color(153, 20, 145, 255));
	cjTx.loadFromImage(cjImg);
	cjSp.setTexture(cjTx);
	cjSp.setOrigin(14, 35);
	cjSp.setPosition(const_player_start_pos_x, const_player_start_pos_y);
}

Player::Player(std::string filename)
{
	onGround = true;
	curPlatform = &PlatformLayer::arrPlatform[0];
	level = 1;
	jumpStrenght = 0;
	xSpeed = 0;
	ySpeed = 0;
	accelerating = false;
	deltaSpeed = 0;

	cjImg.loadFromFile(filename);
	cjImg.createMaskFromColor(sf::Color(153, 20, 145, 255));
	cjTx.loadFromImage(cjImg);
	cjSp.setTexture(cjTx);
	cjSp.setOrigin(14, 35);
	cjSp.setPosition(const_player_start_pos_x, const_player_start_pos_y);
}

int Player::checkBoundaries()
{
	if (cjSp.getPosition().x >= const_left_bound && cjSp.getPosition().x <= const_right_bound)
		return 0;
	else if (cjSp.getPosition().x < const_left_bound)
		return const_left_bound;
	else return const_right_bound;
}

void Player::collide()
{
	static float swat;
	if (jumpStrenght == 3)
	{
		swat = const_dist_between_platforms - 8;
	}
	else swat = const_dist_between_platforms;
	if (cjSp.getPosition().y > - const_dist_between_platforms * level + const_player_start_pos_y + swat) // CONST_BETWEEN_PLATFORM_DISTANCE = 80
	{
		for (Platform& p : PlatformLayer::arrPlatform)
		{
			if (p.getFloor() == level && 
				cjSp.getPosition().x >= p.startSp.getPosition().x - 12.5f && // CONST_START_TILE_WIDTH = 12
				cjSp.getPosition().x <= p.endSp.getPosition().x + 14 + 12.5f) // CONST_END_TILE_WIDTH = 14
			{
				jumpStrenght = 0;
				ySpeed = 0;
				cjSp.setOrigin(14, 35);
				cjSp.setRotation(0);
				cjSp.setPosition(cjSp.getPosition().x, const_player_start_pos_y - const_dist_between_platforms * (level - 1));
				onGround = true;
				curPlatform = &p;
				Score::changeScore((level-1) * 10);
			}
		}
	}
}

void Player::checkCollision()
{
	if  (onGround && 
		!(cjSp.getPosition().x >= curPlatform->startSp.getPosition().x - 12.5f &&
		cjSp.getPosition().x <= curPlatform->endSp.getPosition().x + 14 + 12.5f)) 
	{
		jumpStrenght = 0;
		onGround = false;
		//ySpeed = 0;
	}
}

void Player::animationAndSound(PlatformLayer& pl)
{
	//std::cout << xSpeed << "\n";
	static int i = 0;
	static int j = 0;
	if (!onGround)																										//JUMPING
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
			else cjSp.setTextureRect(Animation::cjAnimJump);
		}
		else
		{
			cjSp.setOrigin(21, 35);
			cjSp.rotate(6);
			cjSp.setTextureRect(Animation::cjAnimRotate);
		}
	}
	else if (cjSp.getPosition().x < const_left_bound + 1)																					//HIT LEFT BOUND
	{
		cjSp.setScale(1, 1);
		cjSp.setTextureRect(Animation::cjAnimWalk1);
	}
	else if (cjSp.getPosition().x > const_right_bound - 1)																				//HIT RIGHT BOUND
	{
		cjSp.setScale(-1, 1);
		cjSp.setTextureRect(Animation::cjAnimWalk1);
	}
	else if (xSpeed > 0 && !checkBoundaries())																			//MOVING
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
	else if (cjSp.getPosition().x >= curPlatform->startSp.getPosition().x - 14 &&										//ON LEFT EDGE
		cjSp.getPosition().x <= curPlatform->startSp.getPosition().x + 12.5f)
	{
		cjSp.setScale(-1, 1);
		if (j < 15)
			cjSp.setTextureRect(Animation::cjAnimEdge1);
		else if (j < 30)
			cjSp.setTextureRect(Animation::cjAnimEdge2);
		else j = 0;
		j++;
	}
	else if (cjSp.getPosition().x >= curPlatform->endSp.getPosition().x &&												//ON RIGHT EDGE
		cjSp.getPosition().x <= curPlatform->endSp.getPosition().x + 14*2)
	{
		cjSp.setScale(1, 1);
		if (j < 15)
			cjSp.setTextureRect(Animation::cjAnimEdge1);
		else if (j < 30)
			cjSp.setTextureRect(Animation::cjAnimEdge2);
		else j = 0;
		j++;
	}
	else if (Camera::getCamLevel() > 0 && cjSp.getPosition().y > pl.getViewCenter() + const_chock_anim_trigger_bound) //CONST_CHOCK_ANIM_BOUND = 400	//CHOCK
	{
		cjSp.setTextureRect(Animation::cjAnimChock);
	}
	else																												//IDLE
	{
		//cjSp.rotate(6);
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
		if (accelerating && xSpeed < const_player_xspeed_max) //CONST_MAX_XSPEED=8
		{
			xSpeed += deltaSpeed;
		}
		else if (xSpeed - deltaSpeed < 0.0f)
		{
			xSpeed = 0.0f;
		}
		else xSpeed -= deltaSpeed;
		cjSp.move(side * xSpeed, 0);
		checkCollision();
	}
	else
	{
		cjSp.setPosition(checkBoundaries(), cjSp.getPosition().y);
		side *= -1;
	}
}

void Player::jump()
{
	if (!onGround)
	{
		cjSp.move(0, ySpeed);
		if (ySpeed < const_player_yspeed_max) //CONST_MAX_YSPEED = 7.5
			ySpeed += const_player_gravity;
		if (ySpeed > 0.0f)
			collide();
	}
}

void Player::checkJump()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		onGround = false;
		if (xSpeed > 5.9f)
		{
			ySpeed = xSpeed * -1.15 - 7.0f; //CONST_XSPEED_JUMP_HIGH_FACTOR
			jumpStrenght = 3;
			cjSp.move(0, 8);
		}
		else if (xSpeed > 2.9f)
		{
			ySpeed = xSpeed * -0.85 - 7.0f; //CONST_XSPEED_JUMP_LOW_FACTOR
			jumpStrenght = 2;
		}
		else
		{
			ySpeed = -7.0f;
			jumpStrenght = 1;
		}
	}
	if (!onGround)
	{
		jump();
	}
	else
	{
		ySpeed = 0.0f;
	}
	level = (cjSp.getPosition().y - const_player_start_pos_y) / -80 + 1;
}

void Player::checkMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (xSpeed > 0 && side == 1)
		{
			accelerating = false;
			deltaSpeed = const_player_slowdown_delta;
			move(); //CONST_SLOWDOWN_DELTA_SPEED
		}
		else
		{
			side = -1;
			accelerating = true;
			deltaSpeed = const_player_accelerate_delta;
			move(); //CONST_ACCELERATE_DELTA_SPEED
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

void Player::checkCam(PlatformLayer& pl)
{
	if ((cjSp.getPosition().y  < pl.getViewCenter() - const_cam_catchup_top_bound))// || //CONST_CATCHUP_TOP_LIMIT = 500
		//(cjSp.getPosition().y - 140 < pl.getViewCenter() - 240 && ySpeed < 0)) //CONST_CATCHUP_BOTTOM_LIMIT = 370;
	{
		if (Camera::getCamSpeed() < const_cam_catchup_top_max_speed) //CONST_CATCHUP_MAXSPEED = 20
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_top_delta_speed * ySpeed * -1); //CONST_YSPEED_FACTOR = 0.066
		else Camera::setCamSpeed(const_cam_catchup_top_max_speed);
	}
	else if (cjSp.getPosition().y < pl.getViewCenter() - const_cam_catchup_bottom_bound && ySpeed < 0)
	{
		if (Camera::getCamSpeed() < const_cam_catchup_bottom_max_speed) //CONST_CATCHUP_MAXSPEED = 20
			Camera::setCamSpeed(Camera::getCamSpeed() + const_cam_catchup_bottom_delta_speed * ySpeed * -1); //CONST_YSPEED_FACTOR = 0.066
		else Camera::setCamSpeed(const_cam_catchup_bottom_max_speed);
	}
	else if (Camera::getCamSpeed() > Camera::getCamLevel())
	{
		Camera::setCamSpeed(Camera::getCamSpeed() - Camera::getCamSpeed() * const_cam_catchup_slowdown_delta_speed); //CONST_SLOWDOWN_FACTOR = 0.05
	}
	else
	{
		Camera::setCamSpeed(Camera::getCamLevel());
	}
}

void Player::checkGameOver(PlatformLayer& pl) //wip
{
	if (cjSp.getPosition().y > pl.getViewCenter() + 240)
	{
		onGround = false;
		Timer::setStarted(false);
		Score::stop();
	}
}

void Player::checkCandy(sf::RenderWindow& window, PlatformLayer& pl)
{
	if (jumpStrenght == 3 && Score::isComboMode()) 
	{
		ece.addCandy(cjSp.getPosition().x, cjSp.getPosition().y);
	}
	ece.doLogic(window, pl);
}

void Player::doLogic(sf::RenderWindow& window, PlatformLayer& pl)
{
	checkJump();
	checkMove();
	checkCam(pl);
	animationAndSound(pl);
	checkGameOver(pl);
	checkCandy(window, pl);

	if (!Timer::getStarted() && cjSp.getPosition().y < const_timer_start_bound)
		Timer::setStarted(true);
}

void Player::render(sf::RenderWindow& window, PlatformLayer& pl)
{
	window.draw(cjSp);
}