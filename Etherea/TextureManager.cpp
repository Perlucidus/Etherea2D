#include "TextureManager.hpp"
#include "Renderer.hpp"

using std::logic_error;

TextureManager::TextureManager(Renderer& renderer) : renderer(renderer) {}

TextureManager& TextureManager::getInstance(Renderer& renderer)
{
	static TextureManager instance(renderer);
	return instance;
}

Texture & TextureManager::GetTexture(string const & id)
{
	auto res = textures.find(id);
	if (res == textures.end())
		throw logic_error("No texture was found by the id of " + id);
	return res->second;
}

void TextureManager::Load(string const& id, string const& path)
{
	if (textures.find(id) != textures.end())
		throw logic_error("There already exists a texture by the id of " + id);
	textures[id] = renderer.LoadTexture(path);
}

void TextureManager::Draw(string const& id, Position const& pos, Size const& size, SDL_RendererFlip flip)
{
	Draw(id, pos, size, Size(0), flip);
}

void TextureManager::Draw(string const& id, Position const& pos, Size const& size, Size const& frame, SDL_RendererFlip flip)
{
	Rect src(static_cast<Position>(size * frame), size), dst(pos, size);
	renderer.CopyEx(textures[id], src, dst, 0, flip);
}
