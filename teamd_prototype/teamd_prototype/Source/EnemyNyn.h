#pragma once
#include "Enemy.h"
#include "Rect2.h"

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
	//手持ちのパラメタ
	struct Parameter {
		Parameter(bool& groundFlag_,const House*& onHouse_,Enemy::State& enemyState_)
			:isGround(groundFlag_),onHouse(onHouse_),enemyState(enemyState_),
			handle(), pos(),size(), vec(), life(),
			prevState(), nowState() {

		}
		int		handle;//画像ハンドル
		Vector2	pos;//座標
		Vector2 size;//おおきさ
		Vector2	vec;//力ベクトル値？
		int		life;//体力
		int		ghostTime;//無敵タイム
		//判定用
		std::vector<CharaCollider*> _collider;

		//基礎クラスがもってるパラメタ
		bool&	isGround;//接地フラグ
		const House*& onHouse;//入ってる家
		Enemy::State& enemyState;//状態
		//state
		EnemyNyn::State*	prevState;
		EnemyNyn::State*	nowState;

		void ChangeState(State* nextState_) {
			if (prevState) { delete prevState; }
			prevState = nowState;
			nowState = nextState_;
		}
	};
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

