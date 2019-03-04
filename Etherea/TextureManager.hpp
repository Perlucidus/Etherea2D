#pragma once

#include "Common.hpp"
#include "Texture.hpp"
#include <map>

using std::map;

class Renderer;
class Rect;

class TextureManager {
public:
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
private:
	explicit TextureManager(Renderer& renderer);
public:
	static TextureManager& getInstance(Renderer&);

	void Load(string const& id, string const& path);
	void Draw(string const& id, Rect const& rect, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(string const& id, Rect const& rect, int fx, int fy = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	Renderer& renderer;
	map<string, Texture> textures;
};
