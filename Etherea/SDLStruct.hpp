#pragma once

#include "Common.hpp"

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

	SDL_Rect* operator->() { return &data; }
	const SDL_Rect* operator->() const { return &data; }
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
private:
	SDL_Point data;
};
