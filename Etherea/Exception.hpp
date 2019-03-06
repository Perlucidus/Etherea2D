#pragma once

#include <exception>

class SDLException : public std::exception {
	const char* what() const noexcept override;
};

class WindowException : public SDLException {};
class RenderException : public SDLException {};
class SurfaceException : public SDLException {};
class TextureException : public SDLException {};

class MixException : public SDLException {
	const char* what() const noexcept override;
};

class MusicException : public MixException {};
class SoundException : public MixException {};
