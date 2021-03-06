#pragma once

#include "Common.hpp"
#include "Exception.hpp"
#include "PixelFormat.hpp"
#include "Vector2D.hpp"
#include <functional>
#include <SDL_render.h>

class Renderer;

using TextureModCallback = std::function<void(PixelFormat const&, Pixel* pixels, size_t pitch, void const* param)>;

class Texture {
	friend class Renderer;
public:
	Texture() = default;
	explicit Texture(SDL_Texture* texture);
	virtual ~Texture() = default;
public:
	bool operator==(Texture const& other) const;

	bool isLoaded() const;
	void Query(Uint32& format, int& access, int& width, int& height);
	void Query(int& width, int& height);
	void Query(Size& size);
	SDL_Color GetColorMod();
	void ColorMod(SDL_Color const& color);
	void ClearColorMod();
	void Modify(TextureModCallback callback, PixelFormat const& format, void const* param);
private:
	void query(Uint32* format = nullptr, int* access = nullptr, int* width = nullptr, int* height = nullptr);
private:
	shared_ptr<SDL_Texture> ptr;
};

class TextureException : public SDLException {};
