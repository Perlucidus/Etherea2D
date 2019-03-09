#include "SoundManager.hpp"
#include "Common.hpp"

using std::logic_error;
using std::runtime_error;

SoundManager::SoundManager() : channels(MIX_CHANNELS), used_channels(0)
{
	Mix_AllocateChannels(channels);
}

SoundManager::~SoundManager()
{
	Mix_AllocateChannels(0);
}

SoundManager& SoundManager::getInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::LoadMusic(string const& path)
{
	music = Music::Load(path);
}

void SoundManager::LoadSample(string const& id, string const& path)
{
	if (samples.find(id) != samples.end())
		throw logic_error("There already exists a sample by the id of " + id);
	samples[id] = Sample::Load(path);
}

int SoundManager::PlaySample(string const& id, int loops, int ms)
{
	if (samples.find(id) == samples.end())
		throw logic_error("No sample was found by the id of " + id);
	AllocateFreeChannels();
	return Mix_PlayChannelTimed(-1, samples[id].ptr.get(), loops, ms);
}

void SoundManager::PlayMusic(int loops)
{
	music.Play(loops);
}

void SoundManager::PlayMusic(int loops, int fade)
{
	music.Play(loops, fade);
}

void SoundManager::PlayMusic(int loops, int fade, double position)
{
	music.Play(loops, fade, position);
}

void SoundManager::SetMusicVolume(float percentage)
{
	music.SetVolume(percentage);
}

void SoundManager::AllocateFreeChannels()
{
	bool allocate = false;
	while (used_channels >= channels) {
		channels += MIX_CHANNELS;
		allocate = true;
	}
	if (allocate)
		if (Mix_AllocateChannels(channels) != channels)
			throw runtime_error("Failed to allocate channels");
}
