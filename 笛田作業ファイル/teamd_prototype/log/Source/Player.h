#pragma once

#include "Rect2.h"


//‘€ì‚·‚él
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw(const Vector2& offset);

	inline const Rect2& Rect() const {
		return _rect;
	}
	inline const Vector2& Vec() const {
		return _vec;
	}
	inline int Weight()const {
		return _weight;
	}

	//setter
	inline void SetPos(const Vector2& pos_) {
		_rect.TelePort(pos_);
	}
	inline void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	void CuddleUp(const Rect2& rect_);

private:
	Vector2		_startPos;

	Rect2		_rect;//À•W‚Æ”ÍˆÍ
	Vector2		_vec;
	int		_weight;

	int _handle;



};

