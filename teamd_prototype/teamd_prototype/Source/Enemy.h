#pragma once

#include "Vector2.h"
#include "Rect2.h"
//Enemy�͂Ԃ�Ȃ��Ă������񂶂�Ȃ��낤��
//��u�ŏ��ł��܂����I


//�G��b
class Camera;
class Player;
class House;
class Enemy
{
public:
	//�����܂��ȏ��
	enum class State {
		unknown,//���ɂȂ��B�킩��Ȃ��B

		isDed,//����
		onHouse,//�����ɉB��Ă�
		isGhost,//�G��Ȃ�
	};
public:
	Enemy();
	virtual ~Enemy();

	virtual int Update() = 0;
	virtual void Draw(const Camera& camera_) = 0;

	Enemy::State GetState() const {
		return __state;
	}
	virtual Vector2 Pos() const = 0;

	inline void SetGroundFlag(bool groundFlag_) {
		__isGround = groundFlag_;
	}
	void SetOnHouse(const House* const house_) {
		__onHouse = house_;
	}
	virtual void SetRect(const Rect2& rect_) = 0;

	//�����蔻��Ɏg��
	virtual Rect2 Rect() const = 0;
	//�����������̏���
	virtual void OnCollided(const Player& player_) {};
	virtual void OnCollided(const House& house_) {};

protected:
	Enemy::State __state = State::unknown;
	bool __isGround = false;
	const House *__onHouse = nullptr;

};

