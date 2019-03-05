#pragma once

#include "SDLStruct.hpp"

class Renderer;

class IRenderable {
public:
	IRenderable() = delete;
	
	IRenderable(string const& id, Position const& pos, Size const& size, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: id(id), pos(pos), size(size), flip(flip) {}
	virtual ~IRenderable() = default;

	virtual void draw(Renderer& renderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	void setFlip(SDL_RendererFlip f) { flip = f; }
protected:
	string id;
	Position pos;
	Size size;
	SDL_RendererFlip flip;
};

class AnimationFrame {
public:
	AnimationFrame() = delete;
	AnimationFrame(Size size, Size current = 0)
		: size(size), current(current) {}

	void set(Size const& frame)
	{
		current = frame;
	}

	void advance(size_t r, size_t c)
	{
		current = current + Size(r, c);
		current.set(current.getX() % size.getX(), current.getY() % size.getY());
	}

	void operator++() { advance(1, 0); }

	Size const& getSize() const { return size; }
	Size const& getFrame() const { return current; }
private:
	Size size, current;
};

class IAnimated : public IRenderable {
public:
	IAnimated() = delete;

	IAnimated(string const& id, Position const& pos, Size const& size,
		AnimationFrame const& frame, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: IRenderable(id, pos, size, flip), frame(frame) {}
	virtual ~IAnimated() = default;
protected:
	AnimationFrame frame;
};
