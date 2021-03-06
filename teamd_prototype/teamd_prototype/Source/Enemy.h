#pragma once

#include "Vector2.h"
#include "Rect2.h"
//Enemyはつぶれなくてもいいんじゃなかろうか
//一瞬で消滅しませい！

enum EnemyName : int{
	NOT_NAME = -1,

	NYN,
	GABYO,

	NUM,
};

//敵基礎
class Camera;
class Player;
class House;
class Enemy
{
public:
	//おおまかな状態
	enum class State {
		unknown,//特になし。わからない。

		isDed,//死去
		onHouse,//建物に隠れてる
		isGhost,//触れない
	};
public:
	Enemy();
	virtual ~Enemy();

	virtual int Update() = 0;
	virtual void Draw(const Camera& camera_) = 0;

	Enemy::State GetState() const {
		return __state;
	}
	unsigned char Name() const {
		return __name;
	}
	virtual Vector2 Pos() const = 0;
	//当たり判定に使う
	virtual Rect2 Rect() const = 0;
	virtual bool IsGround() const = 0;

	inline void SetGroundFlag(bool groundFlag_) {
		__isGround = groundFlag_;
	}
	void SetOnHouse(const House* const house_) {
		__onHouse = house_;
	}
	virtual void SetRect(const Rect2& rect_) = 0;




	//当たった時の処理
	virtual void OnCollided(const Player& player_) {};
	virtual void OnCollided(const House& house_) {};

protected:
	Enemy::State __state = State::unknown;
	bool __isGround = false;
	const House *__onHouse = nullptr;
	unsigned char __name = 0;
};

