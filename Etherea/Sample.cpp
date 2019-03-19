#include "Sample.hpp"
#include "Log.hpp"

Sample::Sample(Mix_Chunk* chunk)
{
	ptr = shared_ptr<Mix_Chunk>(chunk, [=](Mix_Chunk* p) { if (p) Mix_FreeChunk(p); STDLOG << "Chunk Destroyed"; });
	if (ptr) throw SampleException();
}

Sample Sample::Load(string const& path)
{
	return Sample(Mix_LoadWAV(path.c_str()));
}

void Sample::setVolume(float percentage)
{
	Mix_VolumeChunk(ptr.get(), static_cast<int>(MIX_MAX_VOLUME * percentage));
}
