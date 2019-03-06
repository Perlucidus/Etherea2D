#pragma once

#include "Common.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
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

	Texture& GetTexture(string const& id);
	void Load(string const& id, string const& path);
	void Draw(string const& id, Position const& pos, Size const& size, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(string const& id, Position const& pos, Size const& size, Size const& frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	Renderer& renderer;
	map<string, Texture> textures;
};
