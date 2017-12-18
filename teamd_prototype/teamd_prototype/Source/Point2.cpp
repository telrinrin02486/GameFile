#include "Point2.h"
#include <cmath>

#pragma region ‰‰ŽZŽqOR
Point2& Point2::operator+=(const Point2& other_) {
	x += other_.x;
	y += other_.y;
	return *this;
}
Point2& Point2::operator-=(const Point2& other_) {
	x -= other_.x;
	y -= other_.y;
	return *this;
}
Point2& Point2::operator+=(int other_) {
	x += other_;
	y += other_;
	return *this;
}
Point2& Point2::operator-=(int other_) {
	x -= other_;
	y -= other_;
	return *this;
}
Point2& Point2::operator*=(int other_) {
	x *= other_;
	y *= other_;
	return *this;
}
Point2& Point2::operator/=(int other_) {
	x /= other_;
	y /= other_;
	return *this;
}
Point2& Point2::operator%=(int other_) {
	x = x % other_;
	y = y % other_;
	return *this;
}

bool Point2::operator==(const Point2& other_) const {
	return x == other_.x && y == other_.y;
}
bool Point2::operator!=(const Point2& other_) const {
	return !(*this == other_);
}
bool Point2::operator<(const Point2& other_) const {
	return x < other_.x && y < other_.y;
}
bool Point2::operator>(const Point2& other_) const {
	return !(*this < other_);
}
bool Point2::operator<=(const Point2& other_) const {
	return x <= other_.x && y <= other_.y;
}
bool Point2::operator>=(const Point2& other_) const {
	return !(*this <= other_);
}

Point2& Point2::operator-() {
	x = -x;
	y = -y;
	return *this;
}

Point2 operator+(const Point2& l_, const Point2& r_) {
	return Point2(l_.x + r_.x, l_.y + r_.y);
}
Point2 operator-(const Point2& l_, const Point2& r_) {
	return Point2(l_.x - r_.x, l_.y - r_.y);
}


Point2 operator+(const Point2& l_, int r_) {
	return Point2(l_.x + r_, l_.y + r_);
}
Point2 operator-(const Point2& l_, int r_) {
	return Point2(l_.x - r_, l_.y - r_);
}
Point2 operator*(const Point2& l_, int r_) {
	return Point2(l_.x * r_, l_.y * r_);
}
Point2 operator/(const Point2& l_, int r_) {
	return Point2(l_.x / r_, l_.y / r_);
}
Point2 operator%(const Point2& l_, int r_) {
	return Point2(l_.x % r_, l_.y % r_);
}

#pragma endregion

Point2 Point2::Absolute() const {
	return Point2(abs(x), abs(y));
}