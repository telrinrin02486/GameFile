#include "CB_1.h"

#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include <iostream>

#include "Camera.h"


#define MY_RANDOM (rand())
#define HP_RESET(x) ((MY_RANDOM % x))



constexpr char* const imgPaths[] = {
	"../image/humen/boy1.png",
	"../image/humen/boy2.png",
	"../image/humen/boy3.png",
	"../image/humen/boy4.png",
};

CB_1::CB_1(const Rect2& rect_)
	:_rect(rect_){
	//��`���N���X�Ȃ��߂ɁA���������Ƃ��ɂ߂�ǂ������B
	//�N���X�������񂶂�Ȃ��A�݌v�������񂾂��ǂˁH
	Init(rect_);

}


//CB_1::~CB_1()
//{
//}


void CB_1::Init(const Rect2& rect_) {
	_rect = rect_;
	_maxHitPoint = static_cast<unsigned int>(((_rect.Size().x + _rect.Size().y)*0.5f)*1.5f);
	_hitPoint = HP_RESET(_maxHitPoint);
	_durability = 0.5f;
	unsigned int r = rand() % 4;
	_handle = LoadGraph("../image/building2.png");
	_alive = true;
	_vec = Vector2();
	_count = 0;
	_dirx = 2.0f;
	_isRightDir = true;
	_isGround = false;

	//�ǉ�(���X��)
	pattern = MOVE_RETURN;
}
int CB_1::Update() {
	EffectManager& efm = EffectManager::Instance();
	constexpr float gravity = 8.2f * (1.0f / 20.0f);
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	int err = 0;

	//�ǉ�(���X��)
	switch (pattern)
	{
	case MOVE_NORMAL:
	{

	}
	break;
	case MOVE_RETURN:
	{

	}
	break;
	default:
		break;

	}
	//�ړ�
	if (_count++ > 50) {
		_count = 0;
		_dirx = -_dirx;
	}

	_vec.x = _dirx;
	_vec.y += gravity;
	_rect.Move(_vec);

	//�������
	if (_dirx < 0) {
		_isRightDir = false;
	}
	else {
		_isRightDir = true;
	}

	//���S���G�t�F�N�g
	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		efm.EffectCreate(Vector2(_rect.Left() + _rect.Size().x * 0.5f,
			_rect.Bottom() - 80.0f),EFFECT_TYPE::EFFECT_TYPE_SMOKE);
		_alive = false;
		//�n�k�̎g���Â炳�p�Ȃ�
		Camera::Instance().SetEarthquake(Vector2(15.0f, 0.0f));
	}
	return err;
}

void CB_1::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();

	DrawExtendGraphF(s.x,s.y,n.x,n.y,_handle, true);

}
//��ꂿ�Ⴄ���I�I
void CB_1::Crushed(const Player& player) {
	const Rect2 rect = player.Rect();//������̋�`
	const Vector2 vec = player.Vec();//�͂̕���
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = rect;
	
	Rect2 ol = Overlap(pRect, this->Rect());
	
	//float�̌덷�ق�ƌ���
	Vector2 smashedUnit = ol.Size() / 1000.0f;
	float smashedCorrection = 1.0f - _durability;
	Vector2 smashedValue = smashedUnit * smashedCorrection;
	//���x�����ł������Ȃ��B
	Vector2 damageVec = vec;
	Vector2 damageNrmVec = damageVec.Normalize();
	//damageVec = damageNrmVec;
	damageVec = damageVec * static_cast<float>(player.Weight());
	smashedValue = smashedValue * damageVec;
	int damage = static_cast<int>((damageVec.x + damageVec.y) * smashedCorrection);
	int count = 0;
	//�_���[�W�͏c�Ɖ��ŕ������ق��������]
	while (damage > _hitPoint) {
		damage -= _hitPoint;
		_hitPoint = HP_RESET(_maxHitPoint);
		++count;
	}
	_hitPoint -= damage;
	//�Ԃ��ʂ��v�Z
	for (int i = 0; i < count; ++i) {
		int r1 = MY_RANDOM;
		int r2 = MY_RANDOM;
		//����������Βl����Ȃ��Ƃ܂����]
		Vector2 absSize = ol.Size().Absolute();
		Vector2 value = (Vector2(r1, r2) % absSize) * damageNrmVec * 5;
		smashedValue += value;

	
	}

	//�{���Ԃ��ɂ�
	//���g�̍d���Ƃ��A�����Ƃ����낢�낢��]
	//���̕ӂ�͂ǂ�����]�`�H

	_rect.TopCrushed(smashedValue.y);



}


//�ǉ�(���X��)
void CB_1::MoveReturnUpdata()
{
	//�v���C���[���������E�ɂ�����
	/*if (_rect.Left() < �v���C���[)
	{
		_dirx
	}*/
}
