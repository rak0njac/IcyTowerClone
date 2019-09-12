#pragma once
#include <SFML/Audio.hpp>
#include <random>

class PitchedSound : public sf::Sound
{
public:
	using Sound::Sound;
	void playPitched();
};