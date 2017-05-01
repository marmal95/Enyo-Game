#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <utility>

template <typename T>
class Vector : public sf::Vector2<T>
{
public:
	Vector();
	Vector(T x, T y);
	Vector(const Vector<T>& u);
	Vector(const sf::Vector2<T>& u);
	Vector(Vector<T>&& u);

	float magnitude() const;
	void normalize();
	void reverse();

	Vector<T>& operator=(const Vector<T>& u);
	Vector<T>& operator=(const sf::Vector2<T>& u);
	Vector<T>& operator=(Vector<T>&& u);

	// Dot Product
	T operator*(const Vector<T>& u) const;
};

template<typename T>
Vector<T>::Vector()
	: sf::Vector2<T>()
{}

template<typename T>
Vector<T>::Vector(T x, T y)
	: sf::Vector2<T>(x, y)
{}

template<typename T>
Vector<T>::Vector(const Vector<T>& u)
{
	this->x = u.x;
	this->y = u.y;
}

template<typename T>
inline Vector<T>::Vector(const sf::Vector2<T>& u)
{
	this->x = u.x;
	this->y = u.y;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& u)
{
	this->x = std::move(u.x);
	this->y = std::move(u.y);
	u.x = 0;
	u.y = 0;
}

template<typename T>
float Vector<T>::magnitude() const
{
	return static_cast<float>(sqrt(this->x*this->x + this->y*this->y));
}

template<typename T>
void Vector<T>::normalize()
{
	float length = this->magnitude();
	this->x /= length;
	this->y /= length;
}

template<typename T>
void Vector<T>::reverse()
{
	this->x = -this->x;
	this->y = -this->y;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& u)
{
	this->x = u.x;
	this->y = u.y;
	return *this;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const sf::Vector2<T>& u)
{
	this->x = u.x;
	this->y = u.y;
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& u)
{
	this->x = std::move(u.x);
	this->y = std::move(u.y);
	u.x = 0;
	u.y = 0;
	return *this;
}

template<typename T>
T Vector<T>::operator*(const Vector<T>& u) const
{
	return static_cast<float>(this->x * u.x + this->y * u.y);
}