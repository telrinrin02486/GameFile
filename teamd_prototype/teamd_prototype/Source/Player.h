#pragma once

#include "Rect2.h"
#define IMG_DIV_CNT_X 4
#define IMG_DIV_CNT_Y 4
#define IMG_SIZE_X 120
#define IMG_SIZE_Y 120

#define ANIM_SPEED 10

#define EXT_RATE_X 1.0f	//1.0�͓��{
#define EXT_RATE_Y 1.0f
#define PI 3.14

enum ANIM
{
	ANI_WALK,
	ANI_TAMPLE,
	ANI_JUMP,
	ANI_MAX
};

class KeyInput;
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

	Rect2		_rect;//���W�Ɣ͈�
	Vector2		_vec;
	int		_weight;

	int  _handle[IMG_DIV_CNT_Y][IMG_DIV_CNT_X]={};
	ANIM state;
	int aniFram;
	int aniCnt;
	bool isDirRight;


	void setState(KeyInput& key);//����key�ɉ�����state��set
	void setMove();
};

