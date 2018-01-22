#include "EnemyNyn.h"
#include "Camera.h"
#include <DxLib.h>
#include "Player.h"
#include "../House.h"
#include "Collision.h"

#include <cmath>

//うろうろ
class Idle :
	public EnemyNyn::State
{
public:
	Idle(EnemyNyn::Parameter& param_);
	int Update() override;

private:
	int _count;
	int _countMax;
	float _dir;
	float _xMoveValue;

	EnemyNyn::Parameter& _param;

};
//逃げる
class Escaping :
	public EnemyNyn::State {
public:
	Escaping(EnemyNyn::Parameter& param_);
	~Escaping();
	int Update() override;
private:

	EnemyNyn::Parameter& _param;

};
//瀕死
class Dying :
	public EnemyNyn::State {
public:
	Dying(EnemyNyn::Parameter& param_);
	~Dying();
	int Update() override;

private:

	EnemyNyn::Parameter& _param;
};

constexpr float NYN_HEIGHT = 60;
EnemyNyn::EnemyNyn(const Vector2& pos_, const Player& player_)
	:_param(__isGround, __onHouse, __state), _player(player_) {
	_param.nowState = new Idle(_param);
	_param.handle = LoadGraph("../image/ketudakkeNyan.png");
	_param.pos = pos_;
	_param.size = Vector2(50, NYN_HEIGHT);
	_param.life = 30;
	_param.ghostTime = 0;

}


EnemyNyn::~EnemyNyn()
{
}

int EnemyNyn::Update() {
	int err = 0;
	__state = Enemy::State::unknown;
	if (_param.ghostTime > 0) {
		__state = Enemy::State::isGhost;
		--_param.ghostTime;
	}
	if (_param.size.y < 2.0f) {
		__state = Enemy::State::isDed;
	}
	if (__onHouse != nullptr) {
		__state = Enemy::State::onHouse;
	}
	_param.nowState->Update();
	//判定から抜けてる
	if (!_param.collFlag.CalledConf()) {
		//横もしくは縦
		if (_param.collFlag.SideAndBottomHit()) {
			_param.collFlag.ClearSideAndBottomHitFlag();
		}
	}
	_param.collFlag.SetPrevCalledFlag();

	return err;
}
void EnemyNyn::Draw(const Camera& camera_) {
	if (_param.enemyState == Enemy::State::onHouse) {
		return;//描画しません。
	}
	const Rect2 rect = Rect2(_param.pos, _param.size);
	const Vector2 offset = camera_.Offset() + camera_.Pos();
	Point2 s = (rect.LT() - offset).ToPoint2();
	Point2 n = (rect.RB() - offset).ToPoint2();

	DrawExtendGraphF(s.x, s.y, n.x, n.y, _param.handle, true);

	//unsigned int color = 0xffffffff;
	//if (__state == Enemy::State::isGhost) {
	//	color = 0xff00ff00;
	//}
	//DrawBox(s.x, s.y, n.x, n.y, color, false);
	//DrawRectRotaGraph3(s.x,s.y,)

}

void EnemyNyn::OnCollided(const Player& player_) {
	_param.collFlag.SetCalledFlag();
	//横もしくは下からあたってたなら終わり！
	if (_param.collFlag.SideAndBottomHit()) {
		return;
	}
	Rect2 ol = Overlap(player_.Rect(), Rect());
	//方向取得
	Vector2 vec = player_.Vec();
	//上から&&接地ならつぶす
	if (vec.y > 0.0f && ol.W() > ol.H()) {
		if (__isGround) {
			float yMoveValue = ol.H();
			_param.pos.y += yMoveValue;
			_param.size.y -= yMoveValue;
		}
	}
	//横や下からあたってるなら
	//もしくは、接地してない状態の上からなら
	/*if (player_.Vec().x) {*/
	else {
		_param.collFlag.SetSideAndBottomHitFlag();
		//if (__state != Enemy::State::isGhost) {
		Vector2 sPos = player_.Rect().Center();
		sPos.y += player_.Rect().H()*0.5f;
		Vector2 nPos = Rect().Center();
		nPos.y -= Rect().H()*0.5f;

		Vector2 flyVec = (nPos - sPos).Normalize() * 10.0f;
		_param.vec = flyVec;
		_param.pos += _param.vec;
		//_param.ghostTime = 10;
		//}
		Camera& camera = Camera::Instance();
		camera.SetEarthquake(Vector2(3.0f, 0.0f));
	}
	/*}*/
}
//これちょっと難しいなぁ。
void EnemyNyn::OnCollided(const House& house_) {



}
//--

EnemyNyn::State::State() {

}
EnemyNyn::State::~State() {

}

//Idle
Idle::Idle(EnemyNyn::Parameter& param_)
		:_param(param_){
		_count = 0;
		_dir = -1.0f;//初期値は左
		_countMax = (rand() % 150) + 40;
		_xMoveValue = 0.0f;
}

int Idle::Update() {
	int err = 0;
	//前のベクトルの影響をもっておこ
	float prevXVec = _param.vec.x;
	prevXVec = -prevXVec * 0.2f;
	if (fabs(prevXVec) < 0.5f) { prevXVec = 0.0f; }

	if (_param.size.y < NYN_HEIGHT*0.5f) {
		_param.ChangeState(new Dying(_param));
	}
	//if (_param.enemyState == Enemy::State::isGhost) {
	//	_param.ChangeState(new Escaping(_param));
	//}
	constexpr float walkSpeed = 1.0f;
	constexpr float gravity = 9.8f*(1.0f / 30.0f);
	if (_param.isGround) {
		_param.vec.y = 0.0f;
	}
	else if (_count > _countMax) {
		_dir *= -1.0f;
		_count = 0;
		_countMax = (rand() % 150) + 40;
		if (!(_countMax % 2)) {
			_xMoveValue = 0.0f;
		}
		else {
			_xMoveValue = walkSpeed;
		}
	}
	//移動
	if (_param.isGround) {
		_param.vec.x = _dir * _xMoveValue + prevXVec;
	}
	_param.pos += _param.vec;
	//重力加速度追加
	_param.vec.y += gravity;

	++_count;
	return err;
}

//Escape
Escaping::Escaping(EnemyNyn::Parameter& param_)
	:_param(param_) {

}
Escaping::~Escaping() {

}

int Escaping::Update() {
	int err = 0;
	constexpr float escapeSpeed = 7.0f;
	constexpr float gravity = 9.8f*(1.0f / 30.0f);
	if (_param.isGround) {
		_param.vec.y = 0.0f;
	}
	_param.vec.x = escapeSpeed;
	_param.pos += _param.vec;
	//重力加速度追加
	_param.vec.y += gravity;


	return err;
}

//Ded
Dying::Dying(EnemyNyn::Parameter& param_)
	:_param(param_) {

}
Dying::~Dying() {

}
int Dying::Update() {
	int err = 0;
	constexpr float gravity = 9.8f*(1.0f / 30.0f);
	if (_param.isGround) {
		_param.vec = Vector2::ZERO;
	}
	_param.pos += _param.vec;
	//重力加速度追加
	_param.vec.y += gravity;


	return err;
}
