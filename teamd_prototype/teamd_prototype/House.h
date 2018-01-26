#pragma once

#include <vector>
#include "Rect2.h"

class Enemy;
class Camera;
class Player;
//敵が逃げ込むおうち
//今は画像の差異しかないでしょ。
//せめて特殊効果とかぐらい。
//潰れるのがお仕事
//Enemyがこいつを監視した方がやりやすそう
//CB_１とほぼ変わらない実装で。
class House
{
public:
	House(const Vector2& pos_);
	~House();

	int Update();
	void Draw(const Camera& camera_);


	bool IsDead() const {
		return !_alive;
	}

	void Crushed(const Player& player);

	inline const Rect2& Rect() const {
		return _rect;
	}
	inline const Vector2& Vec() const {
		return _vec;
	}

	//setter
	void SetGroundFlag(bool groundFlag_) {
		_isGround = groundFlag_;
	}
	void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	//当たった際の個性的対応
	virtual void OnCollided(const Player& player_);
	virtual void OnCollided(const Enemy& enemy_);
	//横から当たってますよフラグ
	inline bool SideHitFlag() const {
		return _collFlag.SideHit();
	}
private:
	class CollFlag {
	public:
		enum Type : unsigned char{
			//横から当たってましたフラグ用
			sideHit			= 1 << 0,
			verticalHit		= 1 << 1,
			//OnCollided呼ばれましたか関連
			called			= 1 << 2,
			prevCalledFlag	= 1 << 3,
		};
	public:
		CollFlag() :_flag(){}
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
		inline bool CalledConf() const{
			//0121
			//unsigned charなのにtrueかfalseかで比べれるわけないだろぉん・・・
			//数値だよ
			return (_flag & CollFlag::called) != ((_flag & CollFlag::prevCalledFlag) >> 1);
		}
		//横から当たってた
		inline void SetSideHitFlag() {
			ClearVerticalHitFlag();
			_flag |= CollFlag::sideHit;
			
		}
		//sideHitフラグを折る
		inline void ClearSideHitFlag() {
			_flag &= ~CollFlag::sideHit;
		}
		//確認
		inline bool SideHit() const{
			return _flag & CollFlag::sideHit;
		}
		//縦から当たってた
		inline void SetVerticalHitFlag() {
			ClearSideHitFlag();
			_flag |= CollFlag::verticalHit;
		
		}
		//VerticalHitフラグを折る
		inline void ClearVerticalHitFlag() {
			_flag &= ~CollFlag::verticalHit;
		}
		//確認
		inline bool VerticalHit() const {
			return _flag & CollFlag::verticalHit;
		}
	private:
		unsigned char _flag;
	};
private:
	bool	_isGround;
	int		_handle;
	Rect2		_rect;
	bool		_alive;
	unsigned int	_count;
	Vector2		_vec;
	float		_durability;//固さ
	int		_hitPoint;
	int		_maxHitPoint;

	CollFlag	_collFlag;
};
