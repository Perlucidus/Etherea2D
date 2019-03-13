#include "Geometry.hpp"
#include "Common.hpp"
#include <algorithm>

Point::Point() : point(0) {}

Point::Point(Position::Type x, Position::Type y) : point(x, y) {}

Point::Point(int x, int y) : Point(static_cast<Position::Type>(x), static_cast<Position::Type>(y)) {}

Point::Point(Position const& pos) : point(pos) {}

Point::Point(SDL_Point const& pt) : Point(pt.x, pt.y) {}

Position const* Point::operator->() const
{
	return &point;
}

Position* Point::operator->()
{
	return &point;
}

SDL_Point Point::ToSDLPoint() const
{
	SDL_Point pt;
	pt.x = static_cast<int>(point.x);
	pt.y = static_cast<int>(point.y);
	return pt;
}

bool Point::operator==(Point const & other) const
{
	return point.x == other->x && point.y == other->y;
}

bool Point::operator!=(Point const & other) const
{
	return point.x != other->x || point.y != other->y;
}

bool Point::operator<(Point const & other) const
{
	return point.x < other->x && point.y < other->y;
}

bool Point::operator<=(Point const & other) const
{
	return point.x <= other->x && point.y <= other->y;
}

bool Point::operator>(Point const & other) const
{
	return point.x > other->x && point.y > other->y;
}

bool Point::operator>=(Point const & other) const
{
	return point.x >= other->x && point.y >= other->y;
}

Point Point::operator+(Point const & other) const
{
	return Point(point + other.point);
}

Point Point::operator-(Point const & other) const
{
	return Point(point - other.point);
}

Rectangle::Rectangle() : tl(0, 0), br(0, 0) {}

Rectangle::Rectangle(Point const& p1, Point const& p2) : tl(std::min(p1, p2)), br(std::max(p1, p2)) {}

Rectangle::Rectangle(Point const & tl, Size const & size) : tl(tl), br(tl + Point(static_cast<Position>(size))) {}

Rectangle::Rectangle(Position const & tl, Size const & size) : tl(tl), br(tl + static_cast<Position>(size)) {}

Rectangle::Rectangle(Rectangle const& other) : Rectangle(other.tl, other.br) {}

Rectangle::Rectangle(SDL_Rect const& rect) : Rectangle(Point(rect.x, rect.y), Point(rect.x+rect.w,rect.y+rect.h)) {}

float Rectangle::width() const
{
	return br->x - tl->x;
}

float Rectangle::height() const
{
	return br->y - tl->y;
}

void Rectangle::setSize(float width, float height)
{
	br = tl + Point(width, height);
}

bool Rectangle::overlaps(Rectangle const & other) const
{
	return tl < other.br && br > other.tl;
}

SDL_Rect Rectangle::ToSDLRect() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(tl->x);
	rect.y = static_cast<int>(tl->y);
	rect.w = static_cast<int>(width());
	rect.h = static_cast<int>(height());
	return rect;
}

std::ostream & operator<<(std::ostream & out, Point const & pt)
{
	return out << pt.point;
}

std::ostream & operator<<(std::ostream & out, Rectangle const & rect)
{
	return out << rect.tl << (rect.br - rect.tl);
}
