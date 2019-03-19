#pragma once

#include "Vector2D.hpp"
#include <SDL_rect.h>

class Point {
public:
	Point();
	Point(Position::Type x, Position::Type y);
	Point(int x, int y);
	explicit Point(Position const& pos);
	Point(SDL_Point const& pt);

	Position const* operator->() const;
	Position* operator->();

	SDL_Point ToSDLPoint() const;

	bool operator==(Point const& other) const;
	bool operator!=(Point const& other) const;
	bool operator<(Point const& other) const;
	bool operator<=(Point const& other) const;
	bool operator>(Point const& other) const;
	bool operator>=(Point const& other) const;
	Point operator+(Point const& other) const;
	Point operator-(Point const& other) const;

	friend std::ostream& operator<<(std::ostream& out, Point const& pt);
private:
	Position point;
};

class Rectangle {
public:
	Rectangle();
	Rectangle(Point const& p1, Point const& p2);
	Rectangle(Point const& tl, Size const& size);
	Rectangle(Position const& tl, Size const& size);
	Rectangle(Rectangle const& other);
	Rectangle(SDL_Rect const& rect);

	float width() const;
	float height() const;
	void setSize(float width, float height);
	bool overlaps(Rectangle const& other) const;

	SDL_Rect ToSDLRect() const;

	friend std::ostream& operator<<(std::ostream& out, Rectangle const& rect);
public:
	Point tl, br;
};
