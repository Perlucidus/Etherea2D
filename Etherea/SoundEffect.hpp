#pragma once

#include "Common.hpp"

class SoundEffect {
public:
	SoundEffect() = default;
	virtual ~SoundEffect() = default;

	explicit SoundEffect(Mix_Chunk* chunk);

	static SoundEffect Load(string const& path);

	void setVolume(float percentage);
private:
	shared_ptr<Mix_Chunk> ptr;
};
