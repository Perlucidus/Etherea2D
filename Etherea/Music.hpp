#pragma once

#include "SDLStruct.hpp"

class Music {
public:
	Music() = default;
	virtual ~Music() = default;

	explicit Music(Mix_Music* music);

	void play(int loops = 1);
	void play(int loops, int fade);
	void play(int loops, int fade, double position);

	static Music Load(string const& path);
public:
	static const int LOOP_FOREVER;
private:
	shared_ptr<Mix_Music> ptr;
};
