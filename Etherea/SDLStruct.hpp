#pragma once

#include "Common.hpp"
#include "Vector2D.hpp"

class Rect {
	friend class Renderer;
public:
	Rect() { data.x = data.y = data.w = data.h = 0; }
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
		: Rect(static_cast<int>(pos.getX()), static_cast<int>(pos.getY()),
			static_cast<int>(size.getX()), static_cast<int>(size.getY())) {}

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
	Point() { data.x = data.y = 0; }
	Point(Point const& other) : data(other.data) {}
	Point(int x, int y) { data.x = x; data.y = y; }

	SDL_Point* operator->() { return &data; }
	const SDL_Point* operator->() const { return &data; }

	Vector2D<int> const& position() const { return Vector2D<int>(data.x, data.y); }
private:
	SDL_Point data;
};
