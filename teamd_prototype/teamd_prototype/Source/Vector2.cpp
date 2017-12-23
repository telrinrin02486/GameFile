#include "Vector2.h"
#include <cmath>

Vector2 const Vector2::ZERO = { 0.0f,0.0f };

#pragma region ���Z�qOR
Vector2& Vector2::operator+=(const Vector2& other_) {
	x += other_.x;
	y += other_.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& other_) {
	x -= other_.x;
	y -= other_.y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2& other_) {
	x *= other_.x;
	y *= other_.y;
	return *this;
}
Vector2& Vector2::operator/=(const Vector2& other_) {
	x /= other_.x;
	y /= other_.y;
	return *this;
}
Vector2& Vector2::operator%=(const Vector2& other_) {
	x = fmod(x,other_.x);
	y = fmod(y,other_.y);
	return *this;
}

Vector2& Vector2::operator+=(float other_) {
	x += other_;
	y += other_;
	return *this;
}
Vector2& Vector2::operator-=(float other_) {
	x -= other_;
	y -= other_;
	return *this;
}
Vector2& Vector2::operator*=(float other_) {
	x *= other_;
	y *= other_;
	return *this;
}
Vector2& Vector2::operator/=(float other_) {
	x /= other_;
	y /= other_;
	return *this;
}
Vector2& Vector2::operator%=(float other_) {
	x = fmodf(x,other_);
	y = fmodf(y,other_);
	return *this;
}

bool Vector2::operator==(const Vector2& other_) const {
	return x == other_.x && y == other_.y;
}
bool Vector2::operator!=(const Vector2& other_) const {
	return !(*this == other_);
}
bool Vector2::operator<(const Vector2& other_) const {
	return x < other_.x && y < other_.y;
}
bool Vector2::operator>(const Vector2& other_) const {
	return !(*this < other_);
}
bool Vector2::operator<=(const Vector2& other_) const {
	return x <= other_.x && y <= other_.y;
}
bool Vector2::operator>=(const Vector2& other_) const {
	return !(*this <= other_);
}

Vector2& Vector2::operator-() {
	x = -x;
	y = -y;
	return *this;
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
	return Vector2(l_.x * (1.0f / r_.x), l_.y * (1.0f / r_.y));
}
Vector2 operator%(const Vector2& l_, const Vector2& r_) {
	return Vector2(fmod(l_.x ,r_.x), fmod(l_.y , r_.y));
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

#pragma endregion

//----------------------------
Point2 Vector2::ToPoint2() const {
	return Point2(static_cast<int>(x),static_cast<int>(y));
}

float Vector2::Length() const {
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normalize() const {
	float length = this->Length();
	if (length == 0.0f) {
		return Vector2();
	}
	//�ʔ������@�𔭌�
	//�����������m�̊���Z�̏����R�X�g�̌y�����Ǝv����B
	//�R�[�h�̂ݔ����������߁A�ڍׂ͂킩���B
	length = 1.0f / length;
	return *this * length;
}

Vector2 Vector2::Absolute() const{
	return Vector2(fabs(x), fabs(y));
}

float Vector2::Dot() const {
	return x * x + y * y;
}
float Vector2::Dot(const Vector2& other_) const {
	return x * other_.x + y * other_.y;
}
float Vector2::Cross(const Vector2& other_) const {
	return y * other_.x - x * other_.y;
}