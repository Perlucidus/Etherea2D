#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Renderer;

class Texture : public SDLComponent {
	friend class Renderer;
public:
	Texture() = default;
	explicit Texture(SDL_Texture* texture);
	virtual ~Texture() = default;
public:
	void Query(int& width, int& height);
	void Query(Uint32& format, int& access, int& width, int& height);
private:
	void query(Uint32* format = nullptr, int* access = nullptr, int* width = nullptr, int* height = nullptr);
private:
	shared_ptr<SDL_Texture> ptr;
};
