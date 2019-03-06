#include "SoundEffect.hpp"

SoundEffect::SoundEffect(Mix_Chunk * chunk)
{
	ptr = shared_ptr<Mix_Chunk>(chunk, [=](Mix_Chunk* p) { if (p) Mix_FreeChunk(p); STDLOG << "Chunk Destroyed"; });
	if (ptr) throw SoundException();
}

SoundEffect SoundEffect::Load(string const& path)
{
	return SoundEffect(Mix_LoadWAV(path.c_str()));
}

void SoundEffect::setVolume(float percentage)
{
	Mix_VolumeChunk(ptr.get(), static_cast<int>(MIX_MAX_VOLUME * percentage));
}
