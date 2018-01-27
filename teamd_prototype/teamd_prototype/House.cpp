#include "House.h"
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include "Range2.h"
#include <iostream>
#include <string>
#include "Camera.h"
#include <cmath>
#include <DxLib.h>
#include "ImageMng.h"

#define MY_RANDOM (rand())
#define HP_RESET(x) ((MY_RANDOM % x))

//���|�C���^���Œ肵����{���郓�S
const std::string ImagePaths[] = {
	"../image/building2.png",

};
const Vector2 ImageSize[] = {
	Vector2( 130,160 ),
};
const Vector2 ImageDrawSize[] = {
	Vector2(130,160),


};
//�m����Rect�͂킩��Â炢�Ȃ��B
//�l���Ă݂�Ή摜�̓T�C�Y���킩��΂������Ȃ��B

House::House(const Vector2& pos_)
	:_rect(pos_, Vector2(600, 600)) {
	ImageMng* imageMng = ImageMng::GetInstance();
	_maxHitPoint = static_cast<unsigned int>((MY_RANDOM % 300) + 100);
	_hitPoint = HP_RESET(_maxHitPoint);
	_durability = 0.5f;
	_imageSuffix = rand() % sizeof(ImagePaths) / sizeof(std::string);
	_handle = *imageMng->GetImgDivID(ImagePaths[_imageSuffix].c_str(),Vector2(1.0f,1.0f),ImageSize[_imageSuffix]);//�摜�n���h���擾
	_rect.ReSize(ImageSize[_imageSuffix]);
	_alive = true;
	_vec = Vector2();
	_count = 0;
	_isGround = false;
	_isTurn = false;
	_angle = 0.0f;
}


House::~House()
{
}


int House::Update() {
	int err = 0;
	EffectManager& efm = EffectManager::Instance();
	//�d�͉����x�ԈႦ�Ă��E�E�Eʽ޶��
	constexpr float gravity = 9.8f * (1.0f / 20.0f);
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	//������Ή���������ŏd�͕t���Ƃ��Ȃ��Ƃ����Ȃ��H
	_rect.Move(_vec);
	_vec.y += gravity;
	//�O�t���[���œ����蔻�菈�����s�����B
	if (!_collFlag.CalledConf()) {
		//�����瓖�����Ă�H
		if (_collFlag.SideHit()) {
			_collFlag.ClearSideHitFlag();
		}
		//�c���瓖�����Ă�H
		if (_collFlag.VerticalHit()) {
			_collFlag.ClearVerticalHitFlag();
		}
	}
	//�O��Ԃ�ۑ�
	_collFlag.SetPrevCalledFlag();
	//���S���G�t�F�N�g
	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		efm.EffectCreate(Vector2(_rect.Left() + _rect.Size().x * 0.5f,
			_rect.Bottom() - 80.0f), EFFECT_TYPE::EFFECT_TYPE_SMOKE);
		_alive = false;
		//�n�k�̎g���Â炳�p�Ȃ�
		Camera::Instance().SetEarthquake(Vector2(15.0f, 0.0f));
	}
	return err;
}
void House::Draw(const Camera& camera_) {
	Vector2 offset = camera_.Offset() + camera_.Pos();
	Point2 drawPoint = (_rect.Center() - offset).ToPoint2(); ;//�`�悷��ʒu�i���_
	Point2 imageCenter = (ImageDrawSize[_imageSuffix]*0.5f).ToPoint2();//�摜���̂̒��_
	Vector2 scalingRatio = _rect.Size() / ImageSize[_imageSuffix];

	DrawRotaGraph3(drawPoint.x, drawPoint.y,
		imageCenter.x, imageCenter.y,
		scalingRatio.x, scalingRatio.y,
		_angle, _handle, true, _isTurn);
	//unsigned int color = 0x00000000;
	//if (_collFlag.SideHit()) {
	//	color |= 0x00ff00ff;
	//	DrawString(s.x, s.y - 15, "Side", color);
	//}
	//if (_collFlag.VerticalHit()) {
	//	color |= 0xff0000ff;
	//	DrawString(s.x, s.y - 15, "Vertical", color);
	//}
	//if (_collFlag.CalledConf()) {
	//	DrawString(s.x, s.y - 30, "Called", color);
	//}
	//DrawBox(s.x, s.y, n.x, n.y, color, false);

}
//��ꂿ�Ⴄ���I�I
void House::Crushed(const Player& player) {
	const Rect2 rect = player.Rect();//������̋�`
	const Vector2 vec = player.Vec();//�͂̕���
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = rect;

	Rect2 ol = Overlap(pRect, _rect);

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
	_rect.TopCrushed(smashedValue.y);



}

void House::OnCollided(const Player& player_) {
	//�v���F�����瓖�������Ȃ�A������Ȃ��Ȃ�܂ŐG��Ȃ����Ăق���
	//�Ă΂ꂽ��`�F�b�N����
	_collFlag.SetCalledFlag();
	//�����瓖�����Ă邱�ƂɂȂ��Ă�Ȃ�
	if (_collFlag.SideHit()) {
		_collFlag.ClearVerticalHitFlag();
		return;
	}
	//�c���瓖�����Ă邱�ƂɂȂ��Ă�Ȃ�
	if (_collFlag.VerticalHit()) {
		_collFlag.ClearSideHitFlag();
	}

	Rect2 ol = Overlap(player_.Rect(), _rect);
	//�����瓖�����Ă����Ȃ�
	if (ol.W() < ol.H()) {
		_collFlag.SetSideHitFlag();
	}
	//�c�Ȃ�
	else {
		_collFlag.SetVerticalHitFlag();
		//�Ԃ�
		Crushed(player_);
	}

}
void House::OnCollided(const Enemy& enemy_) {

}
