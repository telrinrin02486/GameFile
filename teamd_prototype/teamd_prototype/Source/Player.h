#pragma once

#include "Rect2.h"
#define IMG_DIV_CNT_X 4
#define IMG_DIV_CNT_Y 5
#define IMG_SIZE_X 120
#define IMG_SIZE_Y 120

#define ANIM_SPEED 10

#define EXT_RATE_X 2.2f	//1.0は等倍
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
	//当たり判定用のフラグを理解しやすく利用するためのクラス
	//（理解できるとは言ってない）
	class CollFlag {
	public:
		enum Type : unsigned char {
			//横もしくは下から当たってましたフラグ用
			sideAndBottomHit = 1 << 0,
			//OnCollided呼ばれましたか関連
			called = 1 << 1,
			prevCalledFlag = 1 << 2,
		};
	public:
		CollFlag() :_flag() {}
		//OnCollided呼ばれた
		inline void SetCalledFlag() {
			_flag ^= CollFlag::called;
		}
		//呼ばれたかを前情報として保存
		inline void SetPrevCalledFlag() {
			//もっといい式ありそうだけどよくわかんない（無知）
			//まず消す
			_flag &= ~CollFlag::prevCalledFlag;
			//calledの部分と同じ値にする
			_flag |= (_flag & CollFlag::called) ? CollFlag::prevCalledFlag : 0x00;
		}
		//確認
		//以前呼ばれたか否かは
		//calledとprevCalledFlagの値が異なる場合がtrue
		inline bool CalledConf() const {
			//0121
			//unsigned charなのにtrueかfalseかで比べれるわけないだろぉん・・・
			//数値だよ
			return (_flag & CollFlag::called) != ((_flag & CollFlag::prevCalledFlag) >> 1);
		}
		//横から当たってた
		inline void SetSideAndBottomHitFlag() {
			_flag |= CollFlag::sideAndBottomHit;

		}
		//sideHitフラグを折る
		inline void ClearSideAndBottomHitFlag() {
			_flag &= ~CollFlag::sideAndBottomHit;
		}
		//確認
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

	Rect2		_rect;//座標と範囲
	Vector2		_vec;
	int		_weight;
	bool _isGround;

	int  _handle[IMG_DIV_CNT_Y][IMG_DIV_CNT_X]={};
	ANIM state;
	int aniFram;
	int aniCnt;
	bool isDirRight;

	CollFlag _collFlag;

	void setState(KeyInput& key);//入力keyに応じたstateをset
	void setMove();
};

