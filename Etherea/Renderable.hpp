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
	AnimationFrame(Size size, Size current = Size(0))
		: size(size), current(current) {}

	void set(Size const& frame)
	{
		current = frame;
	}

	void advance(Size const& offset)
	{
		current += offset;
		current.set(current.getX() % size.getX(), current.getY() % size.getY());
	}

	void advance(Uint32 x, Uint32 y) { advance(Size(x, y)); }

	void operator++(int) { advance(1, 0); }

	Size const& getSize() const { return size; }
	Size const& getFrame() const { return current; }
private:
	Size size, current;
};

class IAnimated : public IRenderable {
public:
	IAnimated() = delete;

	IAnimated(string const& id, Position const& pos, Size const& size,
		AnimationFrame const& frame, Uint32 base_fps, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: IRenderable(id, pos, size, flip), frame(frame), prev_update(0), base_fps(base_fps), fps(base_fps) {}
	virtual ~IAnimated() = default;

	virtual void update() override { if (canUpdate()) prev_update = SDL_GetTicks(); }

	bool canUpdate() const { return (SDL_GetTicks() - prev_update) > 1000.f / fps; }
	void setFPS(Uint32 f) { fps = f; }
	void resetFPS() { fps = base_fps; }
protected:
	AnimationFrame frame;
	Uint32 base_fps, fps;
private:
	Uint32 prev_update;
};
