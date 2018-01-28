#pragma once

#include "Rect2.h"
#define IMG_DIV_CNT_X 4
#define IMG_DIV_CNT_Y 5
#define IMG_SIZE_X 120
#define IMG_SIZE_Y 120

#define ANIM_SPEED 10

#define EXT_RATE_X 2.2f	//1.0‚Í“™”{
#define EXT_RATE_Y 2.2f
#define PI 3.14

enum ANIM
{
	ANI_DEF,
	ANI_WALK,
	ANI_WEIGH,
	ANI_JUMP,
	ANI_DAMAGE,
	ANI_MAX
};

class KeyInput;
class Enemy;
class House;
class Player
{
public:
	Player();
	~Player();

	void Update(bool canOperate_);
	void Draw(const Vector2& offset);

	//getter
	inline Vector2 Pos() const {
		return _rect.LT();
	}
	inline const Rect2& Rect() const {
		return _rect;
	}
	inline const Vector2& Vec() const {
		return _vec;
	}
	inline int Weight()const {
		return _weight;
	}
	inline bool IsGround() const{
		return _isGround;
	}


	//setter
	inline void SetPos(const Vector2& pos_) {
		_rect.TelePort(pos_);
	}
	inline void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	inline void SetGroundFlg(bool flg_) {
		_isGround = flg_;
	}

	//collided
	void OnCollided(const Enemy& enemy_);
	void OnCollided(const House& house_);

private:
	Vector2		_startPos;

	Rect2		_rect;//À•W‚Æ”ÍˆÍ
	Vector2		_vec;
	int		_weight;
	bool _isGround;

	int  _handle[IMG_DIV_CNT_Y][IMG_DIV_CNT_X]={};
	ANIM state;
	int aniFram;
	int aniCnt;
	bool isDirRight;


	void setState(KeyInput& key);//“ü—Íkey‚É‰‚¶‚½state‚ğset
	void setMove();
};

