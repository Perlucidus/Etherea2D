#pragma once

#include <cmath>

template<typename IntegerType>
class Vector2D {
public:
	Vector2D();
	explicit Vector2D(IntegerType const& scalar);
	Vector2D(IntegerType const& x, IntegerType const& y);
	Vector2D(Vector2D const&) = default;

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
	Vector2D operator*(IntegerType const& scalar) const;
	Vector2D operator/(IntegerType const& scalar) const;
	Vector2D& operator+=(Vector2D const& other);
	Vector2D& operator-=(Vector2D const& other);
	Vector2D& operator*=(Vector2D const& other);
	Vector2D& operator*=(IntegerType const& scalar);
	Vector2D& operator/=(IntegerType const& scalar);

	operator bool() const;
	template<typename IntegerType2>
	explicit operator Vector2D<IntegerType2>() const;

	IntegerType euclidean_norm() const;
	bool is_normalized() const;
	Vector2D normalized() const;
	void normalize();

	IntegerType const& getX() const;
	IntegerType const& getY() const;
	void setX(IntegerType const& value);
	void setY(IntegerType const& value);
	void set(IntegerType const& valx, IntegerType const& valy);
private:
	IntegerType x, y;
};

using Position = Vector2D<float>;
using Size = Vector2D<Uint32>;
using Direction = Vector2D<float>;
using Velocity = Vector2D<float>;

template<typename IntegerType>
inline Vector2D<IntegerType>::Vector2D() : x(0), y(0) {}

template<typename IntegerType>
inline Vector2D<IntegerType>::Vector2D(IntegerType const & scalar) : x(scalar), y(scalar) {}

template<typename IntegerType>
inline Vector2D<IntegerType>::Vector2D(IntegerType const & x, IntegerType const & y) : x(x), y(y) {}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator==(const Vector2D & other) const
{
	return x == other.x && y == other.y;
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator!=(const Vector2D & other) const
{
	return x != other.x || y != other.y;
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator<=(const Vector2D & other) const
{
	return euclidean_norm() <= other.euclidean_norm();
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator>=(const Vector2D & other) const
{
	return euclidean_norm() >= other.euclidean_norm();
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator<(const Vector2D & other) const
{
	return euclidean_norm() < other.euclidean_norm();
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::operator>(const Vector2D & other) const
{
	return euclidean_norm() > other.euclidean_norm();
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::operator+(Vector2D<IntegerType> const & other) const
{
	return Vector2D(x + other.x, y + other.y);
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::operator-(Vector2D<IntegerType> const & other) const
{
	return Vector2D(x - other.x, y - other.y);
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::operator*(Vector2D<IntegerType> const & other) const
{
	return Vector2D(x * other.x, y * other.y);
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::operator*(IntegerType const & scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::operator/(IntegerType const & scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

template<typename IntegerType>
inline Vector2D<IntegerType> & Vector2D<IntegerType>::operator+=(Vector2D<IntegerType> const & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename IntegerType>
inline Vector2D<IntegerType> & Vector2D<IntegerType>::operator-=(Vector2D<IntegerType> const & other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename IntegerType>
inline Vector2D<IntegerType> & Vector2D<IntegerType>::operator*=(Vector2D<IntegerType> const & other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template<typename IntegerType>
inline Vector2D<IntegerType> & Vector2D<IntegerType>::operator*=(IntegerType const & scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename IntegerType>
inline Vector2D<IntegerType> & Vector2D<IntegerType>::operator/=(IntegerType const & scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

template<typename IntegerType>
inline Vector2D<IntegerType>::operator bool() const
{
	return x || y;
}

template<typename IntegerType>
inline IntegerType Vector2D<IntegerType>::euclidean_norm() const
{
	return static_cast<IntegerType>(std::sqrtl(std::powl(x, 2) + std::powl(y, 2)));
}

template<typename IntegerType>
inline bool Vector2D<IntegerType>::is_normalized() const
{
	return euclidean_norm() == 1;
}

template<typename IntegerType>
inline Vector2D<IntegerType> Vector2D<IntegerType>::normalized() const
{
	IntegerType norm = euclidean_norm();
	if (!norm) throw std::logic_error("Can't normalize a zero vector");
	return *this / norm;
}

template<typename IntegerType>
inline void Vector2D<IntegerType>::normalize()
{
	IntegerType norm = euclidean_norm();
	if (!norm) throw std::logic_error("Can't normalize a zero vector");
	*this /= norm;
}

template<typename IntegerType>
inline IntegerType const & Vector2D<IntegerType>::getX() const
{
	return x;
}

template<typename IntegerType>
inline IntegerType const & Vector2D<IntegerType>::getY() const
{
	return y;
}

template<typename IntegerType>
inline void Vector2D<IntegerType>::setX(IntegerType const & value)
{
	x = value;
}

template<typename IntegerType>
inline void Vector2D<IntegerType>::setY(IntegerType const & value)
{
	y = value;
}

template<typename IntegerType>
inline void Vector2D<IntegerType>::set(IntegerType const & valx, IntegerType const & valy)
{
	x = valx;
	y = valy;
}

template<typename IntegerType>
template<typename IntegerType2>
inline Vector2D<IntegerType>::operator Vector2D<IntegerType2>() const
{
	return Vector2D<IntegerType2>(static_cast<IntegerType2>(x), static_cast<IntegerType2>(y));
}
