#pragma once

#include "Point2.h"

struct Vector2
{
	union {
		float x, y;
		float v[2];
	};
	Vector2();
	Vector2(float x_, float y_)
		:x(x_), y(y_)
	{};
	~Vector2();

	inline Point2 ToPoint2() const{
		return Point2(static_cast<int>(x), static_cast<int>(y));
	}

	Vector2& operator+=(const Vector2& other_);
	Vector2& operator-=(const Vector2& other_);
	Vector2& operator+=(float other_);
	Vector2& operator-=(float other_);
	Vector2& operator*=(float other_);
	Vector2& operator/=(float other_);
	Vector2& operator%=(float other_);

	bool operator==(const Vector2& other_) const;
	bool operator!=(const Vector2& other_) const;
	bool operator<(const Vector2& other_) const;
	bool operator>(const Vector2& other_) const;
	bool operator<=(const Vector2& other_) const;
	bool operator>=(const Vector2& other_) const;
	
	Vector2& operator-();

	//--

	float Length() const;
	Vector2 Normalize() const;
	Vector2 Absolute() const;
	float Dot(const Vector2& other_) const;
	float Cross(const Vector2& other_) const;

};

Vector2 operator+(const Vector2& l_, const Vector2& r_);
Vector2 operator-(const Vector2& l_, const Vector2& r_);
//Vector2 operator*(const Vector2& l_, const Vector2& r_);
//Vector2 operator/(const Vector2& l_, const Vector2& r_);
//Vector2 operator%(const Vector2& l_, const Vector2& r_);

Vector2 operator+(const Vector2& l_, float r_);
Vector2 operator-(const Vector2& l_, float r_);
Vector2 operator*(const Vector2& l_, float r_);
Vector2 operator/(const Vector2& l_, float r_);
Vector2 operator%(const Vector2& l_, float r_);




