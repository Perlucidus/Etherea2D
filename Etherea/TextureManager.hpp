#pragma once

#include "Common.hpp"
#include "Texture.hpp"
#include <map>

using std::map;

class Renderer;

class TextureManager {
public:
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
private:
	explicit TextureManager(Renderer& renderer);
public:
	static TextureManager& getInstance(Renderer&);

	void Load(string const& id, string const& path);
	void Draw(string const& id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(string const& id, int x, int y, int width, int height, int frameX, int frameY = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	Renderer& renderer;
	map<string, Texture> textures;
};
