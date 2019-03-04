#pragma once

#include "SDLStruct.hpp"

class Renderer;

class IRenderable {
public:
	IRenderable() = delete;
	
	IRenderable(string const& id, Rect const& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) : id(id), rect(rect), flip(flip) {}
	virtual ~IRenderable() = default;

	virtual void draw(Renderer& renderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	void setFlip(SDL_RendererFlip f) { flip = f; }
protected:
	string id;
	Rect rect;
	SDL_RendererFlip flip;
};

class AnimationFrame {
public:
	AnimationFrame() = delete;
	AnimationFrame(size_t row_size, size_t column_size, size_t row = 0, size_t column = 0)
		: row_size(row_size), column_size(column_size), row(row), column(column) {}

	void set(size_t r, size_t c)
	{
		row = r;
		column = c;
	}

	void advance(size_t r, size_t c)
	{
		row = (row + r) % row_size;
		column = (column + c + (row + r) / row_size) % column_size;
	}

	void operator++() { advance(1, 0); }

	size_t getRow() const { return row; }
	size_t getColumn() const { return column; }
	size_t getRowSize() const { return row_size; }
	size_t getColumnSize() const { return column_size; }
private:
	size_t row_size, column_size, row, column;
};

class IAnimated : public IRenderable {
public:
	IAnimated() = delete;

	IAnimated(string const& id, Rect const& rect, AnimationFrame const& frame, SDL_RendererFlip flip = SDL_FLIP_NONE)
		: IRenderable(id, rect, flip), frame(frame) {}
	virtual ~IAnimated() = default;
protected:
	AnimationFrame frame;
};
