#include "PitchedSound.h"
#include <iostream>

void PitchedSound::playPitched()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> urd(0.95, 1.15);
	float pitch = urd(mt);

	std::cout << pitch << "\n";
	this->setPitch(pitch);
	this->play();
}