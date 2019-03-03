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

void TextureManager::Draw(string const& id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	Draw(id, x, y, width, height, 0, 0, flip);
}

void TextureManager::Draw(string const& id, int x, int y, int width, int height, int frameX, int frameY, SDL_RendererFlip flip)
{
	Rect src(width * frameX, height * frameY, width, height), dst(x, y, width, height);
	renderer.CopyEx(textures[id], src, dst, 0, flip);
}
