#pragma once

#include "Common.hpp"

class Music {
public:
	Music() = default;
	virtual ~Music() = default;

	explicit Music(Mix_Music* music);

	void Play(int loops = 1);
	void Play(int loops, int fade);
	void Play(int loops, int fade, double position);
	void SetVolume(float percentage);

	static Music Load(string const& path);
private:
	shared_ptr<Mix_Music> ptr;
};
