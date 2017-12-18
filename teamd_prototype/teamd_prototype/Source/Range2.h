#pragma once

#include "Point2.h"

//範囲指定
class Range2
{
public:
	Range2(const Point2& pos_, const Point2& size_)
		:_pos(pos_), _size(size_)
	{}

	//操作。
	void Move(const Point2& mValue_);
	void Move(int dirX_, int dirY_);

	void Teleport(const Point2& pos_);
	void Teleport(int x_, int y_);

	//ゲッタ
	inline int Left() const { return _pos.x; }
	inline int Right() const { return _pos.x +_size.x; }
	inline int Top() const { return _pos.y; }
	inline int Bottom() const { return _pos.y + _size.y; }

	inline Point2 LT() const { return Point2(Left(), Top()); }
	inline Point2 LB() const { return Point2(Left(), Bottom()); }
	inline Point2 RT() const { return Point2(Right(), Top()); }
	inline Point2 RB() const { return Point2(Right(), Bottom()); }

	inline Point2 Center() const {
		return Point2(
			Right() - Size().x / 2,
			Bottom() - Size().y / 2);
	}
	inline Point2 Size() const {
		return Point2(Right() - Left(), Bottom() - Top());
	}
	//向き
	inline bool IsFlont() const {
		return (!(Right() < Left()) || !(Bottom() < Top()));
	}

	//描画
	void Draw(const Point2& offset_, unsigned int color_ = 0xffffffff, bool fillFlag_ = true) const;

private:
	Point2		_pos;
	Point2		_size;


};

