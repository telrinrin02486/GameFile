#pragma once

#include "Rect2.h"
#define IMG_DIV_CNT_X 4
#define IMG_DIV_CNT_Y 5
#define IMG_SIZE_X 120
#define IMG_SIZE_Y 120

#define ANIM_SPEED 10

#define EXT_RATE_X 2.2f	//1.0�͓��{
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
private:
	//�����蔻��p�̃t���O�𗝉����₷�����p���邽�߂̃N���X
	//�i�����ł���Ƃ͌����ĂȂ��j
	class CollFlag {
	public:
		enum Type : unsigned char {
			//���������͉����瓖�����Ă܂����t���O�p
			sideAndBottomHit = 1 << 0,
			//OnCollided�Ă΂�܂������֘A
			called = 1 << 1,
			prevCalledFlag = 1 << 2,
		};
	public:
		CollFlag() :_flag() {}
		//OnCollided�Ă΂ꂽ
		inline void SetCalledFlag() {
			_flag ^= CollFlag::called;
		}
		//�Ă΂ꂽ����O���Ƃ��ĕۑ�
		inline void SetPrevCalledFlag() {
			//�����Ƃ��������肻�������ǂ悭�킩��Ȃ��i���m�j
			//�܂�����
			_flag &= ~CollFlag::prevCalledFlag;
			//called�̕����Ɠ����l�ɂ���
			_flag |= (_flag & CollFlag::called) ? CollFlag::prevCalledFlag : 0x00;
		}
		//�m�F
		//�ȑO�Ă΂ꂽ���ۂ���
		//called��prevCalledFlag�̒l���قȂ�ꍇ��true
		inline bool CalledConf() const {
			//0121
			//unsigned char�Ȃ̂�true��false���Ŕ�ׂ��킯�Ȃ����낧��E�E�E
			//���l����
			return (_flag & CollFlag::called) != ((_flag & CollFlag::prevCalledFlag) >> 1);
		}
		//�����瓖�����Ă�
		inline void SetSideAndBottomHitFlag() {
			_flag |= CollFlag::sideAndBottomHit;

		}
		//sideHit�t���O��܂�
		inline void ClearSideAndBottomHitFlag() {
			_flag &= ~CollFlag::sideAndBottomHit;
		}
		//�m�F
		inline bool SideAndBottomHit() const {
			return _flag & CollFlag::sideAndBottomHit;
		}

	private:
		unsigned char _flag;
	};
public:
	Player(const Vector2 pos_);
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

	Rect2		_rect;//���W�Ɣ͈�
	Vector2		_vec;
	int		_weight;
	bool _isGround;

	int  _handle[IMG_DIV_CNT_Y][IMG_DIV_CNT_X]={};
	ANIM state;
	int aniFram;
	int aniCnt;
	bool isDirRight;

	CollFlag _collFlag;

	void setState(KeyInput& key);//����key�ɉ�����state��set
	void setMove();
};

