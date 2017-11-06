#pragma once

#include "Point2.h"


struct Vector2
{
	float x, y;
	//�����A�����I�y�I�o�ł߂�ǂ��ȁB
	explicit Vector2(float x_ = 0.0f, float y_ = 0.0f)
		:x(x_), y(y_)
	{};
	~Vector2();

	inline Point2 ToPoint2() const{
		return Point2(static_cast<int>(x), static_cast<int>(y));
	}


	Vector2& operator+=(const Vector2& other_) {
		x += other_.x;
		y += other_.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& other_) {
		x -= other_.x;
		y -= other_.y;
		return *this;
	}

	bool operator<(const Vector2& other_) const{
		return x < other_.x && y < other_.y;
	}
	bool operator>(const Vector2& other_) const{
		return !(*this < other_);//�����Z�q���֘A�t����B
	}
	Vector2& operator-() {
		x = -x;
		y = -y;
		return *this;
	}


	float Length() const;
	Vector2 Normalize() const;
	Vector2 Absolute() const;
};

Vector2 operator+(const Vector2& l_, const Vector2& r_);
Vector2 operator-(const Vector2& l_, const Vector2& r_);
Vector2 operator*(const Vector2& l_, const Vector2& r_);
Vector2 operator/(const Vector2& l_, const Vector2& r_);
Vector2 operator%(const Vector2& l_, const Vector2& r_);

//�R���X�g���N�^��explicit�������ꍇ�A
//���L�̗��_�ł���float*Vector2���ł��Ȃ��B
//�Ȃ����͒m���B
//�\�z�F�����炭�A���̂��Ă΂�Ă��B
//����Ő���ɓ����Ӗ���������񂯂ǁB
//�f�t�H���g�������O���ƂȂ�܂���B
Vector2 operator+(const Vector2& l_, float r_);
Vector2 operator-(const Vector2& l_, float r_);
Vector2 operator*(const Vector2& l_, float r_);
Vector2 operator/(const Vector2& l_, float r_);
Vector2 operator%(const Vector2& l_, float r_);




