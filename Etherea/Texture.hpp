#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Renderer;

class Texture : public SDLComponent {
	friend class Renderer;
public:
	Texture() = delete;

	explicit Texture(SDL_Texture* texture);
	virtual ~Texture();
private:
	Texture(Texture const& other);
public:
	void Query(Uint32& format, int& access, int& width, int& height);
private:
	SDL_Texture* ptr;
};
