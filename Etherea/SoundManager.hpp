#pragma once

#include "Sample.hpp"
#include "Music.hpp"
#include <map>

class SoundManager {
public:
	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;
private:
	SoundManager();
public:
	static SoundManager& getInstance();

	void LoadMusic(string const& path);
	void LoadSample(string const& id, string const& path);
	int PlaySample(string const& id, int loops = 1, int ms = LOOP_SOUND_FOREVER);
	void PlayMusic(int loops = 1);
	void PlayMusic(int loops, int fade);
	void PlayMusic(int loops, int fade, double position);

	void SetMusicVolume(float percentage);
private:
	void AllocateFreeChannels();
private:
	std::map<string, Sample> samples;
	Music music;
	int channels, used_channels;
};
