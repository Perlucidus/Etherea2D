#pragma once

#include "Common.hpp"

class Surface {
	friend class Renderer;
public:
	Surface() = default;
	virtual ~Surface() = default;

	explicit Surface(SDL_Surface* surface);

	static Surface LoadIMG(string const& path);

	void GetColorMod(Uint8& r, Uint8& g, Uint8& b);
	void ColorMod(Uint8 r, Uint8 g, Uint8 b);
	void ClearColorMod();
	void GetAlphaMod(Uint8& alpha);
	void AlphaMod(Uint8 alpha);
	void ClearAlphaMod();
private:
	shared_ptr<SDL_Surface> ptr;
};
