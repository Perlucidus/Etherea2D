#include "TextureManager.hpp"
#include "Renderer.hpp"

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

void TextureManager::Draw(string const& id, Position const& pos, Size const& size, SDL_RendererFlip flip)
{
	Draw(id, pos, size, 0, flip);
}

void TextureManager::Draw(string const& id, Position const& pos, Size const& size, Size const& frame, SDL_RendererFlip flip)
{
	//Rect src(static_cast<Position const>(size * frame, size)), dst(pos, size);
	//renderer.CopyEx(textures[id], src, dst, 0, flip);
}
