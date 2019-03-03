#pragma once

#include "Common.hpp"

class Surface {
	friend class Renderer;
public:
	Surface() = default;
	virtual ~Surface() = default;

	explicit Surface(SDL_Surface* surface);
public:
	static Surface LoadIMG(string const& path);
private:
	class SurfaceDeleter;
private:
	shared_ptr<SDL_Surface> ptr;
};
