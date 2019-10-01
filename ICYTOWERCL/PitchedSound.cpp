#include "PitchedSound.h"

void PitchedSound::playPitched()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> urd(0.9, 1.3);
	float pitch = urd(mt);

	this->setPitch(pitch);
	this->play();
}