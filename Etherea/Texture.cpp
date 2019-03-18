#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture)
{
	ptr = shared_ptr<SDL_Texture>(texture, [=](SDL_Texture* p) { if (p) SDL_DestroyTexture(p); STDLOG << "Texture Destroyed"; });
	if (!ptr) throw TextureException();
}

void Texture::Query(int & width, int & height)
{
	query(nullptr, nullptr, &width, &height);
}

void Texture::Query(Size & size)
{
	int w, h;
	Query(w, h);
	size = Size(w, h);
}

bool Texture::operator==(Texture const & other) const
{
	return ptr == other.ptr;
}

bool Texture::isLoaded() const
{
	return ptr.get();
}

void Texture::Query(Uint32& format, int& access, int& width, int& height)
{
	query(&format, &access, &width, &height);
}

SDL_Color Texture::GetColorMod()
{
	SDL_Color color;
	if (SDL_GetTextureColorMod(ptr.get(), &color.r, &color.g, &color.b) || SDL_GetTextureAlphaMod(ptr.get(), &color.a))
		throw SurfaceException();
	return color;
}

void Texture::ColorMod(SDL_Color const& color)
{
	if (SDL_SetTextureColorMod(ptr.get(), color.r, color.g, color.b) || SDL_SetTextureAlphaMod(ptr.get(), color.a))
		throw SurfaceException();
}

void Texture::ClearColorMod()
{
	SDL_Color color;
	color.r = color.g = color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	ColorMod(color);
}

void Texture::Modify(TextureModCallback callback, PixelFormat const& format, void const* param)
{
	void* pixels;
	int pitch;
	if (SDL_LockTexture(ptr.get(), nullptr, &pixels, &pitch) || pitch < 0)
		throw TextureException();
	try {
		callback(format, static_cast<Pixel*>(pixels), static_cast<size_t>(pitch) / sizeof(Pixel), param);
	}
	catch (...) {
		SDL_UnlockTexture(ptr.get());
		throw;
	}
}

void Texture::query(Uint32* format, int* access, int* width, int* height)
{
	if (SDL_QueryTexture(ptr.get(), format, access, width, height))
		throw TextureException();
}
