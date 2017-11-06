#pragma once

#include "Point2.h"

//�͈͎w��
struct Range2
{
	Point2		_sPos, _nPos;

	Range2(const Point2& sPos_, const Point2& nPos_)
		:_sPos(sPos_), _nPos(nPos_)
	{}

	inline int Left() const { return _sPos.x; }
	inline int Right() const { return _nPos.x; }
	inline int Top() const { return _sPos.y; }
	inline int Bottom() const { return _nPos.y; }

	inline Point2 LT() const { return Point2(Left(), Top()); }
	inline Point2 LB() const { return Point2(Left(), Bottom()); }
	inline Point2 RT() const { return Point2(Right(), Top()); }
	inline Point2 RB() const { return Point2(Right(), Bottom()); }

	inline Point2 Center() const {
		return Point2(
			Right() - Left() / 2,
			Bottom() - Top() / 2);
	}

	//--
	//�l�̑��
	inline void Left(int left_){ _sPos.x = left_; }
	inline void Right(int right_){ _nPos.x = right_; }
	inline void Top(int top_) { _sPos.y = top_; }
	inline void Bottom(int bottom_ ) { _nPos.y = bottom_; }

	////����B
	//void Move(const Point2& mValue_);
	//void Move(int dirX_, int dirY_);

	//void Teleport(const Point2& pos_);
	//void Teleport(int x_, int y_);

	////�`��i�����呤�ł��̂߂�ǂ��Ƃ��Ɏg���B
	//void Draw(int handle_, bool transFlag_ = true) const;

private:



};

