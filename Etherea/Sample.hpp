#pragma once

#include "Common.hpp"

class Sample {
	friend class SoundManager;
public:
	Sample() = default;
	virtual ~Sample() = default;

	explicit Sample(Mix_Chunk* chunk);

	static Sample Load(string const& path);

	void setVolume(float percentage);
private:
	shared_ptr<Mix_Chunk> ptr;
};
