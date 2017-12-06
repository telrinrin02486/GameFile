#pragma once

#include "Point2.h"

//1206_後ほど編集予定
struct Vector2
{
	float x, y;
	//あぁ、こいつオペオバでめんどいな。
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
		return !(*this < other_);//←演算子を関連付ける。
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

//コンストラクタにexplicitをつけた場合、
//下記の利点であるfloat*Vector2ができない。
//なぜかは知らん。
//予想：おそらく、↑のが呼ばれてた。
//それで正常に動く意味が分からんけど。
//デフォルト引数を外すとなりません。
Vector2 operator+(const Vector2& l_, float r_);
Vector2 operator-(const Vector2& l_, float r_);
Vector2 operator*(const Vector2& l_, float r_);
Vector2 operator/(const Vector2& l_, float r_);
Vector2 operator%(const Vector2& l_, float r_);




