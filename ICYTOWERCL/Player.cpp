#include <Player.h>
#include <iostream>
#include <PlatformLayer.h>

bool falling = false;
bool jumping = true;
bool onGround = true;

Platform* curPlatform = &PlatformLayer::arrPlatform[0];
int level = 1;
float indexer = 0;
float PosX = 140;
float PosY = -126;  //383
float curPos = PosY;
sf::Image cjImg;
sf::Texture cjTx;
sf::Sprite cjSp;
int key;
float speed = 0;

void Player::init()
{
	cjImg.loadFromFile("..\\Assets\\harold.bmp");
	cjImg.createMaskFromColor(sf::Color(153, 20, 145, 255));
	cjTx.loadFromImage(cjImg);
	cjSp.setTexture(cjTx);
	cjSp.setTextureRect(sf::IntRect(3, 5, 29, 51));
	cjSp.setOrigin(14.5f, -508);
	cjSp.setPosition(PosX, PosY);
}

int checkBoundaries()
{
	if (PosX >= 87 && PosX <= 555)
		return 0;
	else if (PosX < 87)
		return 87;
	else return 555;
}


void collide() // WORK IN PROGRESS;
{
	if (cjSp.getPosition().y > - 80*level - 46)
	{
		for (Platform& p : PlatformLayer::arrPlatform)
		{
			if (p.floor == level && cjSp.getPosition().x >= p.startSp.getPosition().x - 12 && cjSp.getPosition().x <= p.endSp.getPosition().x +14 + 12)
			{
				std::cout << "\nBINGO!";
				std::cout << "\nstartSp pos: " << p.startSp.getPosition().x;
				std::cout << "\nplayer pos: " << cjSp.getPosition().x;
				std::cout << "\nendSp pos: " << p.endSp.getPosition().x;
				cjSp.setPosition(cjSp.getPosition().x, -126 - 80 * (level - 1));
				onGround = true;
				jumping = true;
				falling = false;
				curPlatform = &p;
			}
		}
	}
	//std::cout << "colliding";
	for (Platform p : PlatformLayer::arrPlatform)
	{
		//std::cout << "x: " << p.startSp.getPosition().x << " y: " << p.startSp.getPosition().y << "\n";
	}
	//static int i = 0;
	//if (i == 40)
	//{
	//	onGround = true;
	//	i = 0;
	//	return;
	//}
	//i++;
}

void checkCollision()
{
	if (cjSp.getPosition().x >= curPlatform->startSp.getPosition().x && cjSp.getPosition().x <= curPlatform->endSp.getPosition().x + 14)
	{
		std::cout << "\nStill on platform.";
		std::cout << "\nstartSp pos: " << curPlatform->startSp.getPosition().x;
		std::cout << "\nplayer pos: " << cjSp.getPosition().x;
		std::cout << "\nendSp pos: " << curPlatform->endSp.getPosition().x;
		//cjSp.setPosition(cjSp.getPosition().x, -126 - 80 * (level - 1));
		//onGround = true;
		//curPlatform = &p;
	}
	else if(onGround)
	{
		jumping = false;
		falling = false;
		onGround = false;
		std::cout << "\nFell from platform.";
		std::cout << "\nstartSp pos: " << curPlatform->startSp.getPosition().x;
		std::cout << "\nplayer pos: " << cjSp.getPosition().x;
		std::cout << "\nendSp pos: " << curPlatform->endSp.getPosition().x;
	}
}

void move(bool accelerate, float delta)
{
	if (!checkBoundaries())
	{
		if (accelerate)
		{
			if (speed < 8)
			{
				speed += delta;
			}
		}
		else if (speed - delta < 0)
		{
			speed = 0;
		}
		else speed -= delta;
		cjSp.move(key * speed, 0);
		PosX = cjSp.getPosition().x;
		checkCollision();
	}
	else
	{
		cjSp.setPosition(checkBoundaries(), cjSp.getPosition().y);
		PosX = cjSp.getPosition().x;
		key *= -1;
		speed *= 0.5f;
	}
}

void jump() // WORK IN PROGRESS
{
	static int jumpStep = 0;
	static float i = 0;
	//std::cout << "\ncpos: " << curPos << "\nPosY: " << PosY;
	//std::cout << i << "\n";
	if (!onGround)
	{
		cjSp.move(0, i - fabs(speed)*0.5);
		PosY = cjSp.getPosition().y;
		//std::cout << "ok: " << curPos;
		if (jumping)
		{
			if (i > -4)
			{
				i -= 0.16;
			}
			else
			{
				jumping = false;
				falling = true;
			}
		}
		if (falling)
		{
			if (i < 4)
			{
				i += 0.16;
			}
			if (i > 0)
			{
				collide();
			}
		}
		level = (cjSp.getPosition().y + 126) / 80 * -1 + 1 ;
		//std::cout << "level: " << level << " pos: " << cjSp.getPosition().y << "\n";
		jumpStep++;
	}
	else
	{
		i = 0;
		jumpStep = 0;
		jumping = true;
		falling = false;
		return;
	}
}

void fall()
{
	static float i = 0;
	std::cout << "FALLINNGGGG";
	if (!onGround)
	{
		cjSp.move(0, i);
		i += 0.02;
		collide();
	}
	else
	{
		i = 0;
		return;
	}
	level = (cjSp.getPosition().y + 126) / 80 * -1 + 1;
}
	//else
	//{
	//	jumping = true;
	//	falling = false;
	//	return;
	//}
//}

void Player::checkControls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		onGround = false;
		jump();
	}
	else if (jumping || falling)
		jump();
	else fall();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (speed > 0 && key == 1)
		{
			move(false, 0.5);
		}
		else
		{
			key = -1;
			move(true, 0.07);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (speed > 0 && key == -1)
		{
			move(false, 0.5);
		}
		else
		{
			key = 1;
			move(true, 0.07);
		}
	}
	else
	{
		if (speed > 0)
		{
			move(false, 0.07);
		}
		else key = 0;
	}
}



void Player::render(sf::RenderWindow& window)
{
	window.draw(cjSp);
}