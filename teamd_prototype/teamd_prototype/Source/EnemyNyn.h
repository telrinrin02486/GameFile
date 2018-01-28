#pragma once
#include "Enemy.h"
#include "Rect2.h"

#include <vector>

class CharaCollider;

class Player;
class House;
class Camera;
class EnemyNyn :
	public Enemy
{
public:
	//状態基礎クラス
	class State {
	public:
		State();
		virtual ~State();

		virtual int Update() = 0;

	};
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
	//手持ちのパラメタ
	struct Parameter {
		Parameter(bool& groundFlag_, const House*& onHouse_, Enemy::State& enemyState_,
			unsigned char& name_)
			:isGround(groundFlag_), onHouse(onHouse_), enemyState(enemyState_),
			enemyName(name_),
			handle(), pos(), size(), vec(), life(),
			prevState(), nowState()
		{}
		int		handle;//画像ハンドル
		Vector2	pos;//座標
		Vector2 size;//おおきさ
		Vector2	vec;//力ベクトル値？
		int		life;//体力
		int		ghostTime;//無敵タイム
		int		imageSuffix;//画像識別番号
		float	angle;//回転値
		bool	isTurn;//side
		CollFlag collFlag;//フラグ群
						  //判定用
		std::vector<CharaCollider*> _collider;

		//基礎クラスがもってるパラメタ
		bool&	isGround;//接地フラグ
		const House*& onHouse;//入ってる家
		Enemy::State& enemyState;//状態
		unsigned char& enemyName;//お名前
								 //state
		EnemyNyn::State*	prevState;
		EnemyNyn::State*	nowState;

		void ChangeState(State* nextState_) {
			if (prevState) { delete prevState; }
			prevState = nowState;
			nowState = nextState_;
		}
	};
private:
	class Idle;
	class Escaping;
	class Dying;
public:
	EnemyNyn(const Vector2& pos_,const Player& player_);
	~EnemyNyn();

	int Update() override;
	void Draw(const Camera& camera_) override;
	Vector2 Pos() const override {
		return _param.pos;
	}
	Rect2 Rect() const override {
		return Rect2(_param.pos, _param.size);
	}
	bool IsGround() const override {
		return _param.isGround;
	}

	void SetRect(const Rect2& rect_) override{
		_param.pos = rect_.LT();
		_param.size = rect_.Size();
	}

	void OnCollided(const Player& player_) override;
	void OnCollided(const House& house_) override;

private:
	Parameter _param;

	const Player& _player;
};

