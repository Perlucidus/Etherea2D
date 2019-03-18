#pragma once

#include <cmath>
#include <ostream>

template<typename FType>
class Vector2D {
public:
	Vector2D();
	explicit Vector2D(FType const& scalar);
	Vector2D(FType const& x, FType const& y);
	Vector2D(Vector2D const&);

	Vector2D& operator=(Vector2D const&) = default;
	bool operator==(Vector2D const& other) const;
	bool operator!=(Vector2D const& other) const;
	bool operator<=(Vector2D const& other) const;
	bool operator>=(Vector2D const& other) const;
	bool operator<(Vector2D const& other) const;
	bool operator>(Vector2D const& other) const;
	Vector2D operator+(Vector2D const& other) const;
	Vector2D operator-(Vector2D const& other) const;
	Vector2D operator*(Vector2D const& other) const;
	Vector2D operator*(FType const& scalar) const;
	Vector2D operator/(FType const& scalar) const;
	Vector2D& operator+=(Vector2D const& other);
	Vector2D& operator-=(Vector2D const& other);
	Vector2D& operator*=(Vector2D const& other);
	Vector2D& operator*=(FType const& scalar);
	Vector2D& operator/=(FType const& scalar);

	template<typename FType2>
	explicit operator Vector2D<FType2>() const;

	FType euclidean_norm() const;
	bool is_normalized() const;
	Vector2D normalized() const;
	void normalize();

	template<typename FType>
	friend std::ostream& operator<<(std::ostream& out, Vector2D<FType> vec);
public:
	typedef FType Type;

	FType x, y;
};

using Position = Vector2D<float>;
using Size = Vector2D<uint32_t>;
using Direction = Vector2D<float>;
using Velocity = Vector2D<float>;

template<typename FType>
inline Vector2D<FType>::Vector2D() : x(0), y(0) {}

template<typename FType>
inline Vector2D<FType>::Vector2D(FType const & scalar) : x(scalar), y(scalar) {}

template<typename FType>
inline Vector2D<FType>::Vector2D(FType const & x, FType const & y) : x(x), y(y) {}

template<typename FType>
inline Vector2D<FType>::Vector2D(Vector2D const & other) : x(other.x), y(other.y) {}

template<typename FType>
inline bool Vector2D<FType>::operator==(const Vector2D & other) const
{
	return x == other.x && y == other.y;
}

template<typename FType>
inline bool Vector2D<FType>::operator!=(const Vector2D & other) const
{
	return x != other.x || y != other.y;
}

template<typename FType>
inline bool Vector2D<FType>::operator<=(const Vector2D & other) const
{
	return euclidean_norm() <= other.euclidean_norm();
}

template<typename FType>
inline bool Vector2D<FType>::operator>=(const Vector2D & other) const
{
	return euclidean_norm() >= other.euclidean_norm();
}

template<typename FType>
inline bool Vector2D<FType>::operator<(const Vector2D & other) const
{
	return euclidean_norm() < other.euclidean_norm();
}

template<typename FType>
inline bool Vector2D<FType>::operator>(const Vector2D & other) const
{
	return euclidean_norm() > other.euclidean_norm();
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::operator+(Vector2D<FType> const & other) const
{
	return Vector2D(x + other.x, y + other.y);
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::operator-(Vector2D<FType> const & other) const
{
	return Vector2D(x - other.x, y - other.y);
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::operator*(Vector2D<FType> const & other) const
{
	return Vector2D(x * other.x, y * other.y);
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::operator*(FType const & scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::operator/(FType const & scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

template<typename FType>
inline Vector2D<FType> & Vector2D<FType>::operator+=(Vector2D<FType> const & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename FType>
inline Vector2D<FType> & Vector2D<FType>::operator-=(Vector2D<FType> const & other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename FType>
inline Vector2D<FType> & Vector2D<FType>::operator*=(Vector2D<FType> const & other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template<typename FType>
inline Vector2D<FType> & Vector2D<FType>::operator*=(FType const & scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename FType>
inline Vector2D<FType> & Vector2D<FType>::operator/=(FType const & scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

template<typename FType>
inline FType Vector2D<FType>::euclidean_norm() const
{
	return static_cast<FType>(std::sqrtl(std::powl(x, 2) + std::powl(y, 2)));
}

template<typename FType>
inline bool Vector2D<FType>::is_normalized() const
{
	return euclidean_norm() == 1;
}

template<typename FType>
inline Vector2D<FType> Vector2D<FType>::normalized() const
{
	FType norm = euclidean_norm();
	if (!norm) throw std::logic_error("Can't normalize a zero vector");
	return *this / norm;
}

template<typename FType>
inline void Vector2D<FType>::normalize()
{
	FType norm = euclidean_norm();
	if (!norm) throw std::logic_error("Can't normalize a zero vector");
	*this /= norm;
}

template<typename FType>
template<typename FType2>
inline Vector2D<FType>::operator Vector2D<FType2>() const
{
	return Vector2D<FType2>(static_cast<FType2>(x), static_cast<FType2>(y));
}

template<typename FType>
inline std::ostream & operator<<(std::ostream & out, Vector2D<FType> vec)
{
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}
