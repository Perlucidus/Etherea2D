#pragma once

#include <exception>

class SDLException : public std::exception {
public:
	char const* what() const noexcept override;
};

class MixException : public SDLException {
public:
	char const* what() const noexcept override;
};

class WindowException : public SDLException {};
class RenderException : public SDLException {};
class SurfaceException : public SDLException {};
class TextureException : public SDLException {};
class PixelFormatException : public SDLException {};
class TimerException : public SDLException {
public:
	TimerException();
	TimerException(char const* reason);

	char const* what() const noexcept override;
private:
	char const* reason;
};

class MusicException : public MixException {};
class SampleException : public MixException {};
