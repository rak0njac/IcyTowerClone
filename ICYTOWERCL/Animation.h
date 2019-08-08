#pragma once
#include <SFML/Graphics.hpp>

class Animation {
private:

public:
	static sf::IntRect cjAnimIdle1;// (3, 4, 28, 52);
	static sf::IntRect cjAnimWalk1;// (36, 4, 28, 52);
	static sf::IntRect cjAnimWalk2;// (69, 4, 28, 52);
	static sf::IntRect cjAnimWalk3;// (103, 4, 28, 52);
	static sf::IntRect cjAnimWalk4;// (137, 4, 28, 52);
	static sf::IntRect cjAnimJump1;// (171, 4, 28, 52);
	static sf::IntRect cjAnimJump2;// (205, 4, 28, 52);
	static sf::IntRect cjAnimJump3;// (239, 4, 28, 52);
	static sf::IntRect cjAnimJump;// (273, 4, 28, 58);
	static sf::IntRect cjAnimIdle2;// (307, 4, 28, 52);
	static sf::IntRect cjAnimIdle3;// (340, 4, 28, 52);
	static sf::IntRect cjAnimChock;// (373, 4, 28, 52);
	static sf::IntRect cjAnimRotate;// (407, 4, 42, 60);
	static sf::IntRect cjAnimEdge2;// (456, 4, 35, 51);
	static sf::IntRect cjAnimEdge1;// (498, 4, 35, 51);
	static void init();
};
