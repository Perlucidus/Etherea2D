#pragma once

#include "Common.hpp"
#include "Vector2D.hpp"

class Rect {
	friend class Renderer;
public:
	Rect() { SDL_zero(data); }
	Rect(Rect const& other) : data(other.data) {}
	Rect(int width, int height) : Rect(0, 0, width, height) {}
	Rect(int x, int y, int width, int height)
	{
		data.x = x;
		data.y = y;
		data.w = width;
		data.h = height;
	}
	Rect(Position const& pos, Size const& size)
		: Rect(static_cast<int>(pos.x), static_cast<int>(pos.y),
			static_cast<int>(size.x), static_cast<int>(size.y)) {}

	SDL_Rect* operator->() { return &data; }
	const SDL_Rect* operator->() const { return &data; }

	Vector2D<int> const& position() const { return Vector2D<int>(data.x, data.y); }
	Vector2D<int> const& size() const { return Vector2D<int>(data.w, data.h); }
private:
	SDL_Rect data;
};

class Point {
	friend class Renderer;
public:
	Point() { SDL_zero(data); }
	Point(Point const& other) : data(other.data) {}
	Point(int x, int y) { data.x = x; data.y = y; }

	SDL_Point* operator->() { return &data; }
	const SDL_Point* operator->() const { return &data; }

	Vector2D<int> const& position() const { return Vector2D<int>(data.x, data.y); }
private:
	SDL_Point data;
};
