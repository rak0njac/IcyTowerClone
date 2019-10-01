#include <FloorTypes.h>

sf::IntRect FloorTypes::SnowX(0, 0, 25, 37);
sf::IntRect FloorTypes::IceX(0, 38, 25, 37);
sf::IntRect FloorTypes::WoodX(0, 76, 21, 21);
sf::IntRect FloorTypes::BlueX(4, 98, 17, 12);
sf::IntRect FloorTypes::PinkGooX(5, 111, 17, 19);
sf::IntRect FloorTypes::BoneX(7, 131, 16, 16);
sf::IntRect FloorTypes::LianaX(5, 148, 16, 16);
sf::IntRect FloorTypes::MarioX(5, 167, 16, 19);
sf::IntRect FloorTypes::CloudX(4, 187, 18, 25);
sf::IntRect FloorTypes::RainbowX(1, 213, 18, 12);

sf::IntRect FloorTypes::SnowY(25, 0, 16, 37);
sf::IntRect FloorTypes::IceY(25, 38, 16, 37);
sf::IntRect FloorTypes::WoodY(21, 76, 16, 21);
sf::IntRect FloorTypes::BlueY(21, 98, 17, 12);
sf::IntRect FloorTypes::PinkGooY(22, 111, 14, 19);
sf::IntRect FloorTypes::BoneY(23, 131, 14, 16);
sf::IntRect FloorTypes::LianaY(21, 148, 17, 16);
sf::IntRect FloorTypes::MarioY(21, 167, 15, 19);
sf::IntRect FloorTypes::CloudY(22, 187, 15, 25);
sf::IntRect FloorTypes::RainbowY(19, 213, 19, 12);

sf::IntRect FloorTypes::SnowZ(41, 0, 17, 37);
sf::IntRect FloorTypes::IceZ(41, 38, 17, 37);
sf::IntRect FloorTypes::WoodZ(37, 76, 21, 21);
sf::IntRect FloorTypes::BlueZ(38, 98, 17, 12);
sf::IntRect FloorTypes::PinkGooZ(36, 111, 17, 19);
sf::IntRect FloorTypes::BoneZ(37, 131, 15, 16);
sf::IntRect FloorTypes::LianaZ(38, 148, 13, 16);
sf::IntRect FloorTypes::MarioZ(36, 167, 18, 19);
sf::IntRect FloorTypes::CloudZ(37, 187, 19, 25);
sf::IntRect FloorTypes::RainbowZ(38, 213, 19, 12);

std::vector<sf::IntRect> FloorTypes::getIntRects(int type)
{
	std::vector<sf::IntRect> vec;

	switch (type)
	{
	case Snow:
		vec.push_back(SnowX);
		vec.push_back(SnowY);
		vec.push_back(SnowZ);
		return vec;
	case Ice:
		vec.push_back(IceX);
		vec.push_back(IceY);
		vec.push_back(IceZ);
		return vec;
	case Wood:
		vec.push_back(WoodX);
		vec.push_back(WoodY);
		vec.push_back(WoodZ);
		return vec;
	case Blue:
		vec.push_back(BlueX);
		vec.push_back(BlueY);
		vec.push_back(BlueZ);
		return vec;
	case PinkGoo:
		vec.push_back(PinkGooX);
		vec.push_back(PinkGooY);
		vec.push_back(PinkGooZ);
		return vec;
	case Bone:
		vec.push_back(BoneX);
		vec.push_back(BoneY);
		vec.push_back(BoneZ);
		return vec;
	case Liana:
		vec.push_back(LianaX);
		vec.push_back(LianaY);
		vec.push_back(LianaZ);
		return vec;
	case Mario:
		vec.push_back(MarioX);
		vec.push_back(MarioY);
		vec.push_back(MarioZ);
		return vec;
	case Cloud:
		vec.push_back(CloudX);
		vec.push_back(CloudY);
		vec.push_back(CloudZ);
		return vec;
	case Rainbow:
		vec.push_back(RainbowX);
		vec.push_back(RainbowY);
		vec.push_back(RainbowZ);
		return vec;
	}
}