#pragma once

#include "Common.hpp"

class Renderer;

class Texture {
	friend class Renderer;
public:
	Texture() = default;
	explicit Texture(SDL_Texture* texture);
	virtual ~Texture() = default;
public:
	void Query(int& width, int& height);
	void Query(Uint32& format, int& access, int& width, int& height);
	void GetColorMod(Uint8& r, Uint8& g, Uint8& b);
	void ColorMod(Uint8 r, Uint8 g, Uint8 b);
	void ClearColorMod();
	void GetAlphaMod(Uint8& alpha);
	void AlphaMod(Uint8 alpha);
	void ClearAlphaMod();
private:
	void query(Uint32* format = nullptr, int* access = nullptr, int* width = nullptr, int* height = nullptr);
private:
	shared_ptr<SDL_Texture> ptr;
};
