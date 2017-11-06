#include "Vector2.h"


#include <cmath>

Vector2::~Vector2()
{
}


Vector2 operator+(const Vector2& l_, const Vector2& r_) {
	return Vector2(l_.x + r_.x, l_.y + r_.y);
}
Vector2 operator-(const Vector2& l_, const Vector2& r_) {
	return Vector2(l_.x - r_.x, l_.y - r_.y);
}
Vector2 operator*(const Vector2& l_, const Vector2& r_) {
	return Vector2(l_.x * r_.x, l_.y * r_.y);
}
Vector2 operator/(const Vector2& l_, const Vector2& r_) {
	return Vector2(l_.x / r_.x, l_.y / r_.y);
}
Vector2 operator%(const Vector2& l_, const Vector2& r_) {
	return Vector2(fmod(l_.x , r_.x), fmod(l_.y , r_.y));
}

Vector2 operator+(const Vector2& l_, float r_) {
	return Vector2(l_.x + r_, l_.y + r_);
}
Vector2 operator-(const Vector2& l_, float r_) {
	return Vector2(l_.x - r_, l_.y - r_);
}
Vector2 operator*(const Vector2& l_, float r_) {
	return Vector2(l_.x * r_, l_.y * r_);
}
Vector2 operator/(const Vector2& l_, float r_) {
	return Vector2(l_.x / r_, l_.y / r_);
}
Vector2 operator%(const Vector2& l_, float r_) {
	return Vector2(fmod(l_.x , r_), fmod(l_.y , r_));
}

float Vector2::Length() const {
	return sqrt(x*x + y*y);
}


Vector2 Vector2::Normalize() const {
	return *this / Length();
}

Vector2 Vector2::Absolute() const{
	return Vector2(fabs(x), fabs(y));
}