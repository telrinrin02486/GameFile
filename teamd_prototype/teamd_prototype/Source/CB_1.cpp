#include "CB_1.h"

#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include <iostream>

#include "Camera.h"

//�����̕��z���킩���
//�m���Arand���Ƃ΂炯���l���ł�B
//�Ȃ߂炩�ȗ����͕K�v���H
#define MY_RANDOM (rand())
#define HP_RESET ((MY_RANDOM % 400) + 100)

CB_1::CB_1(EffectManager& efm_, float durability_)
	:_efm(efm_),_rect(CB1_RECT), _durability(durability_)
{
	_handle = LoadGraph("../image/yaju.jpg");
	_alive = true;
	_hitPoint = HP_RESET;
}


//CB_1::~CB_1()
//{
//}



int CB_1::Update() {
	int err = 0;

	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		_efm.EffectCreate(Vector2(_rect.Left() + _rect.size.x * 0.5f,
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
	//�����g�������Ń������g���������I
	//�R���p�C�����̊��蓖�Ă�������v���낤���ǁA
	//�����X�؂��Ƃ܂����]
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = player.Rect();
	
	Rect2 ol = Overlap(pRect, this->Rect());
	
	//float�̌덷�ق�ƌ���
	Vector2 smashedUnit = ol.size / 1000.0f;
	float smashedCorrection = 1.0f - _durability;
	Vector2 smashedValue = smashedUnit * smashedCorrection;
	Vector2 damageVec = player.Vec();
	Vector2 damageNrmVec = damageVec.Normalize();
	damageVec = damageNrmVec;
	damageVec = damageVec * static_cast<float>(player.Weight());
	smashedValue = smashedValue * damageVec;
	int damage = static_cast<int>((damageVec.x + damageVec.y) * smashedCorrection);
	int count = 0;
	//�_���[�W�͏c�Ɖ��ŕ������ق��������]
	while (damage > _hitPoint) {
		damage -= _hitPoint;
		_hitPoint = HP_RESET;
		++count;
	}
	_hitPoint -= damage;
	//�Ԃ��ʂ��v�Z
	for (int i = 0; i < count; ++i) {
		int r1 = MY_RANDOM;
		int r2 = MY_RANDOM;
		//����������Βl����Ȃ��Ƃ܂����]

		Vector2 absSize = ol.size.Absolute();
		Vector2 value = (Vector2(r1, r2) % absSize) * damageNrmVec * 5;
		smashedValue += value;

		//�����ŃJ������炷�]
		Camera::Instance().SetEarthquake(Vector2(10.0f, 2.0f));
	}
	
	//��Y�����ɂ����Ԃ��ĂȂ�����A
	//X�����̒l�������Ȃ������ˁB
	_rect.TopCrushed(smashedValue.y);

}
