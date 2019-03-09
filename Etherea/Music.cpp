#include "Music.hpp"

Music::Music(Mix_Music* music) {
	ptr = shared_ptr<Mix_Music>(music, [=](Mix_Music* p) { if (p) Mix_FreeMusic(p); STDLOG << "Music Destroyed"; });
	if (!ptr) throw MusicException();
}

void Music::Play(int loops)
{
	if (Mix_PlayMusic(ptr.get(), loops))
		throw MusicException();
}

void Music::Play(int loops, int fade)
{
	if (Mix_FadeInMusic(ptr.get(), loops, fade))
		throw MusicException();
}

void Music::Play(int loops, int fade, double position)
{
	if (Mix_FadeInMusicPos(ptr.get(), loops, fade, position))
		throw MusicException();
}

void Music::SetVolume(float percentage)
{
	Mix_VolumeMusic(static_cast<int>(MIX_MAX_VOLUME * percentage));
}

Music Music::Load(string const & path)
{
	return Music(Mix_LoadMUS(path.c_str()));
}
