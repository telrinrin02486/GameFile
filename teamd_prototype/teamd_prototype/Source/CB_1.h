#pragma once

#include "CrushedBox.h"
#include "Rect2.h"

//壊れ方１
//■をつぶすだけ。

class Player;

class CB_1 :
	public CrushedBox
{
public:
	CB_1(const Rect2& rect_);
	~CB_1()
	{}

	//何パターンか忘れた。
	//メモリ再確保したくないから、initでデータだけ入れて使いまわす。
	void Init(const Rect2& rect_);
	int Update() override;
	void Draw(const Vector2& offset_) override;

	bool IsDead() const {
		return !_alive;
	}

	void Crushed(const Player& player);

	inline const Rect2& Rect() const {
		return _rect;
	}


	//セッタ
	void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	void SetGroundFlg(bool flg_) {
		_isGround = flg_;
	}
private:
	bool	_isGround;
	int		_handle;
	Rect2		_rect;
	bool		_alive;
	bool		_isRightDir;
	unsigned int	_count;
	Vector2		_vec;
	float		_dirx;
	float		_durability;//固さ
	int		_hitPoint;
	int		_maxHitPoint;

};

