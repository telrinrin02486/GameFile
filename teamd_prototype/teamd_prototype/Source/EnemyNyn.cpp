#include "EnemyNyn.h"
#include "Camera.h"
#include <DxLib.h>
#include "Player.h"
#include "../House.h"
#include "Collision.h"
#include "../BloodManager.h"
#include <cmath>
#include "ImageMng.h"
#include <string>

//���낤��
class EnemyNyn::Idle :
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
//������
class EnemyNyn::Escaping :
	public EnemyNyn::State {
public:
	Escaping(EnemyNyn::Parameter& param_);
	~Escaping();
	int Update() override;
private:

	EnemyNyn::Parameter& _param;

};
//�m��
class EnemyNyn::Dying :
	public EnemyNyn::State {
public:
	Dying(EnemyNyn::Parameter& param_);
	~Dying();
	int Update() override;

private:

	EnemyNyn::Parameter& _param;
};

//-----------------------------------
const std::string IMAGE_PATH[] = {
	"../image/humen/boy1.png",
	"../image/humen/boy2.png",
	"../image/humen/boy3.png",
	"../image/humen/boy4.png",
	"../image/humen/girl1.png",
	"../image/humen/girl2.png",
	"../image/humen/girl3.png",
	"../image/humen/girl4.png",
	"../image/humen/girl5.png",
	"../image/humen/girl6.png",
};
const Vector2 IMAGE_SIZE[] = { 
	{68,142},
	{55,126},
	{58,136},
	{64,136},
	{61,128},
	{60,140},
	{58,139},
	{71,144},
	{59,137},
	{59,127},
};

constexpr float NYN_HEIGHT = 60;
EnemyNyn::EnemyNyn(const Vector2& pos_, const Player& player_)
	:_param(__isGround, __onHouse, __state,__name), _player(player_) 
{
	ImageMng* imageMng = ImageMng::GetInstance();

	_param.nowState = new Idle(_param);
	_param.imageSuffix = rand() % (sizeof(IMAGE_PATH) / sizeof(std::string));
	_param.handle = *imageMng->GetImgDivID(IMAGE_PATH[_param.imageSuffix],Vector2(1,1),IMAGE_SIZE[_param.imageSuffix]);
	_param.pos = pos_;
	_param.size = Vector2(40, NYN_HEIGHT);
	_param.life = 30;
	_param.ghostTime = 0;
	_param.enemyName = EnemyName::NYN;
	_param.angle = 0.0f;
	_param.isTurn = false;//�G���炵�āAfalse�͉E�Atrue�͍�

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
	//���肩�甲���Ă�
	if (!_param.collFlag.CalledConf()) {
		//���������͏c
		if (_param.collFlag.SideAndBottomHit()) {
			_param.collFlag.ClearSideAndBottomHitFlag();
		}
	}
	_param.collFlag.SetPrevCalledFlag();

	return err;
}
void EnemyNyn::Draw(const Camera& camera_) {
	if (_param.enemyState == Enemy::State::onHouse) {
		return;//�`�悵�܂���B
	}
	const Rect2 rect = Rect2(_param.pos, _param.size);

	Vector2 offset = camera_.Offset() + camera_.Pos();
	Point2 drawPoint = (rect.Center() - offset).ToPoint2(); ;//�`�悷��ʒu�i���_
	Point2 imageCenter = (IMAGE_SIZE[_param.imageSuffix] * 0.5f).ToPoint2();//�摜���̂̒��_
	Vector2 scalingRatio = (rect.Size() / IMAGE_SIZE[_param.imageSuffix]);//_rect.Size() / ImageSize[_imageSuffix];//�`��䗦�i�Ԃ�K��

	DrawRotaGraph3(drawPoint.x, drawPoint.y,
		imageCenter.x, imageCenter.y,
		scalingRatio.x, scalingRatio.y,
		_param.angle, _param.handle, true, _param.isTurn);

}

void EnemyNyn::OnCollided(const Player& player_) {
	_param.collFlag.SetCalledFlag();
	//���������͉����炠�����Ă��Ȃ�I���I
	if (_param.collFlag.SideAndBottomHit()) {
		return;
	}
	Rect2 ol = Overlap(player_.Rect(), Rect());
	//�����擾
	Vector2 vec = player_.Vec();
	//�ォ��&&�ڒn�Ȃ�Ԃ�
	if ((vec.y > 0.0f && ol.W() > ol.H()) || vec.y > abs(vec.x) + 5.0f ) {
		if (__isGround) {
			float yMoveValue = ol.H();
			_param.pos.y += yMoveValue;
			_param.size.y -= yMoveValue;
			//�Ԃꂽ�T�C�Y�������o���܂���
			int bloodNum = static_cast<int>(yMoveValue * 0.5f);
			BloodManager& bloodMng = BloodManager::Instance();
			for (int i = 0; i < bloodNum; ++i) {
				//���������o����������߂܂�
				Vector2 flyVec = -(player_.Vec() * 0.25f);
				float xDif = static_cast<float>((rand() % 60) - 30);//-30~30
				float yDif = static_cast<float>((rand() % 30) - 15);//-15~15
				flyVec.x += xDif;
				flyVec.y += yDif;
				bloodMng.Create(Rect().Center(), flyVec);
			}
		}
	}
	//���≺���炠�����Ă�Ȃ�
	//�������́A�ڒn���ĂȂ���Ԃ̏ォ��Ȃ�
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
		//�����ō��W�𒼐ڂ�����B
		_param.pos += _param.vec;
		//_param.ghostTime = 10;
		//}
		Camera& camera = Camera::Instance();
		camera.SetEarthquake(Vector2(3.0f, 0.0f));
	}
	/*}*/
}
//���ꂿ����Ɠ���Ȃ��B
void EnemyNyn::OnCollided(const House& house_) {

	//_param.nowState->OnCollided(house_);


}
//--

EnemyNyn::State::State() {

}
EnemyNyn::State::~State() {

}

//Idle
EnemyNyn::Idle::Idle(EnemyNyn::Parameter& param_)
		:_param(param_){
		_count = 0;
		_dir = -1.0f;//�����l�͍�
		_countMax = (rand() % 150) + 40;
		_xMoveValue = 0.0f;
}

int EnemyNyn::Idle::Update() {
	int err = 0;
	//�O�̃x�N�g���̉e���������Ă���
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
	//�ړ�
	if (_param.isGround) {
		_param.vec.x = _dir * _xMoveValue + prevXVec;
	}
	_param.pos += _param.vec;
	//�d�͉����x�ǉ�
	_param.vec.y += gravity;
	//�����ݒ�
	if (_dir < 0.0f) { _param.isTurn = true; }
	if (_dir > 0.0f) { _param.isTurn = false; }

	++_count;
	return err;
}

//Escape
EnemyNyn::Escaping::Escaping(EnemyNyn::Parameter& param_)
	:_param(param_) {

}
EnemyNyn::Escaping::~Escaping() {

}

int EnemyNyn::Escaping::Update() {
	int err = 0;
	constexpr float escapeSpeed = 7.0f;
	constexpr float gravity = 9.8f*(1.0f / 30.0f);
	if (_param.isGround) {
		_param.vec.y = 0.0f;
	}
	_param.vec.x = escapeSpeed;
	_param.pos += _param.vec;
	//�d�͉����x�ǉ�
	_param.vec.y += gravity;


	return err;
}

//Ded
EnemyNyn::Dying::Dying(EnemyNyn::Parameter& param_)
	:_param(param_) {

}
EnemyNyn::Dying::~Dying() {

}
int EnemyNyn::Dying::Update() {
	int err = 0;
	constexpr float gravity = 9.8f*(1.0f / 30.0f);
	if (_param.isGround) {
		_param.vec = Vector2::ZERO;
	}
	_param.pos += _param.vec;
	//�d�͉����x�ǉ�
	_param.vec.y += gravity;


	return err;
}
