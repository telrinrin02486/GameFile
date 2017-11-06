#pragma once

#include "Vector2.h"
#include "Range2.h"

//矩形
//sizeがマイナスになると、ゲッタの値が予想と違うものが流れる
//可能性がある。
struct Rect2
{
	Vector2		pos, size;

	explicit Rect2(const Vector2& ltPos_ = Vector2(), const Vector2& size_ = Vector2())
		:pos(ltPos_), size(size_)
	{}

	void Move(const Vector2& dir_);
	void TelePort(const Vector2& pos_);

	void TopCrushed(const float y_);
	void BottomCrushed(const float y_);
	void LeftCrushed(const float x_);
	void RightCrushed(const float x_);

	inline float Left() const { return pos.x; }
	inline float Right() const { return pos.x + size.x; }
	inline float Top() const { return pos.y; }
	inline float Bottom() const { return pos.y + size.y; }

	inline Vector2 LT() const { return Vector2(Left(), Top()); }
	inline Vector2 LB() const { return Vector2(Left(), Bottom()); }
	inline Vector2 RT() const { return Vector2(Right(), Top()); }
	inline Vector2 RB() const { return Vector2(Right(), Bottom()); }

	inline Vector2 Center() const {
		return Vector2(
			Right() - Left() * 0.5f,
			Bottom() - Top() * 0.5f);
	}

	inline Range2 ToRange() const {
		return Range2(pos.ToPoint2(), (pos + size).ToPoint2());
	}

	void Draw(const Vector2& offset_,unsigned int color_ = 0xffffffff, bool fillFlag_ = true) const;

};

