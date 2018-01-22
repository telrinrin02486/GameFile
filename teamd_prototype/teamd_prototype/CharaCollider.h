#pragma once

#include "Rect2.h"

class Player;
class Enemy;
class House;


class CharaCollider
{
public:
	CharaCollider(const Rect2& rect_);
	~CharaCollider();

	virtual void OnCollided(const Player* const player_) {}
	virtual void OnCollided(const Enemy* const enemy_) {}
	virtual void OnCollided(const House* const house_) {}
	//class‚É‚·‚éˆÓ–¡ŠF–³‚ÈŒ`‚â‚Ë
	inline const Rect2& Rect() const{
		return _rect;
	}
	inline void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	inline void Move(const Vector2& moveValue_) {
		_rect.Move(moveValue_);
	}

private:
	Rect2	_rect;
};

