#pragma once

#include "Vector2.h"
#include "BloodManager.h"

//血
//Enemyから吹き出る
//あしまんはこれを吸収、強化

//量が多いので、処理を一か所にまとめる方法をとってみる

//管理が更新と描画をするぅ
//それ以外に別途方法があるならそれも              

class Blood
{
	friend BloodManager;
public:
	Blood()
		:_pos(), _vec(),_isAlive(),_isGround()
	{}
	Blood(const Vector2& pos_, const Vector2& vec_)
		:_pos(pos_), _vec(vec_), _isAlive(true),_isGround()
	{}

	inline void SetGroundFlag(bool flag_) {
		_isGround = flag_;
	}
	inline bool IsGround() const {
		return _isGround;
	}
	//キャストにかかるコストとメモリを圧迫するコスト
	//どっちを優先しようかな

private:
	Vector2		_pos;//座標
	Vector2		_vec;//方向
	bool		_isAlive;//生死判定
	bool		_isGround;//接地フラグ
};

