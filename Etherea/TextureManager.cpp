#include "TextureManager.hpp"
#include "Renderer.hpp"
#include "SDLStruct.hpp"

TextureManager::TextureManager(Renderer& renderer) : renderer(renderer) {}

TextureManager& TextureManager::getInstance(Renderer& renderer)
{
	static TextureManager instance(renderer);
	return instance;
}

void TextureManager::Load(string const& id, string const& path)
{
	textures[id] = renderer.LoadTexture(path);
}

void TextureManager::Draw(string const& id, Rect const& rect, SDL_RendererFlip flip)
{
	Draw(id, rect, 0, 0, flip);
}

void TextureManager::Draw(string const& id, Rect const& rect, int fx, int fy, SDL_RendererFlip flip)
{
	Rect src(rect->w * fx, rect->h * fy, rect->w, rect->h), dst(rect->x, rect->y, rect->w, rect->h);
	renderer.CopyEx(textures[id], src, dst, 0, flip);
}
