#pragma once
#include <SFML/Graphics.hpp>

class FloorTypes
{
private:
	static sf::IntRect SnowX;
	static sf::IntRect IceX;
	static sf::IntRect WoodX;
	static sf::IntRect BlueX;
	static sf::IntRect PinkGooX;
	static sf::IntRect BoneX;
	static sf::IntRect LianaX;
	static sf::IntRect MarioX;
	static sf::IntRect CloudX;
	static sf::IntRect RainbowX;

	static sf::IntRect SnowY;
	static sf::IntRect IceY;
	static sf::IntRect WoodY;
	static sf::IntRect BlueY;
	static sf::IntRect PinkGooY;
	static sf::IntRect BoneY;
	static sf::IntRect LianaY;
	static sf::IntRect MarioY;
	static sf::IntRect CloudY;
	static sf::IntRect RainbowY;

	static sf::IntRect SnowZ;
	static sf::IntRect IceZ;
	static sf::IntRect WoodZ;
	static sf::IntRect BlueZ;
	static sf::IntRect PinkGooZ;
	static sf::IntRect BoneZ;
	static sf::IntRect LianaZ;
	static sf::IntRect MarioZ;
	static sf::IntRect CloudZ;
	static sf::IntRect RainbowZ;

public:
	static enum Type
	{
		Snow,
		Ice,
		Wood,
		Blue,
		PinkGoo,
		Bone,
		Liana,
		Mario,
		Cloud,
		Rainbow,
		Count
	};
	static std::vector<sf::IntRect> getIntRects(int type);
};