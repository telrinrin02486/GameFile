#include "Camera.h"

#include <cmath>


//Shaker--------------------------------



//Camera------------------------------------


Camera::Camera(const Vector2& pos_)
	:_pos(pos_) {
}


Camera::~Camera()
{
}

//�X�V
void Camera::Update() {
	//�V�F�C�N
	if (_shakeFuncPtr != nullptr) {
		_state = Camera::Earthquake;
		if ((this->*_shakeFuncPtr)()) {
			_state = Camera::Idel;
			_shakeFuncPtr = nullptr;
		}
	}

}

//���ݒn����ړ�
void Camera::Move(float dirX_, float dirY_) {
	_pos += Vector2(dirX_, dirY_);

}
void Camera::Move(const Vector2& dir_) {
	_pos += dir_;

}
//�e���|�[�g
void Camera::Teleport(float posX_, float posY_) {
	_pos = Vector2(posX_, posY_);
}
void Camera::Teleport(const Vector2& pos_) {
	_pos = pos_;
}

void Camera::SetEarthquake(	const Vector2& shakeValue_,
							float reductionRate_,
							float speed_) {

	//init 
	_reductionRate = reductionRate_;
	_shakeSpeed = speed_;
	_shakeValue += shakeValue_;
	_nowShakeValue = Vector2();
	_length = Vector2();
	_offset = _shakeValue;

	//�h��l�̒���
	_shakeValue = -(_shakeValue - (_shakeValue * _reductionRate));
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),fabs(_shakeValue.y) + fabs(_offset.y));//����
	_nowLength = Vector2();
	if (_shakeValue.x == 0.0f && _shakeValue.y == 0.0f) {
		_shakeFuncPtr = nullptr;
		return;
	}
	_shakeFuncPtr = &Camera::Shake;

}
void Camera::SetPermanentEarthquake(const Vector2& shakeValue_,float speed_ ) {
	_shakeValue += shakeValue_;
	_shakeSpeed = speed_;
	_offset = _shakeValue;

	//�h���ݒ�
	_shakeValue = -_shakeValue;
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//����
	_nowLength = Vector2();

	_shakeFuncPtr = &Camera::ShakeForever;
}

void Camera::StopEarthquake() {
	_offset = Vector2();
	_shakeFuncPtr = nullptr;

}


//���̃V�F�C�N�͗h����������Ă邪�A
//�]�C��������A�Ȃ߂炩�ȗh��͑Ή����Ă��Ȃ��B
//�߂�l�F�֐��|�C���^�������@true:�����āI�@false:���̂܂܂��Ƃ���
bool Camera::Shake() {
	bool flg = false;
	if (_length.x - _nowLength.x >= 1.0f){ 
		_offset.x += _nowShakeValue.x;
		_nowLength.x += fabs(_nowShakeValue.x);
		flg = true;
	}
	if (_length.y - _nowLength.y >= 1.0f) {
		_offset.y += _nowShakeValue.y;
		_nowLength.y += fabs(_nowShakeValue.y);
		flg = true;
	}
	if (flg) { return false; }

	//�h���ݒ�
	_shakeValue = -(_shakeValue - (_shakeValue * _reductionRate));
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//����
	_nowLength = Vector2();
	//�����؂�グ
	if (fabs(_shakeValue.x) < 1.0f && fabs(_shakeValue.y) < 1.0f) {
		_offset = Vector2();
		return true;
	}

	return false;


}
bool Camera::ShakeForever() {
	bool flg = false;
	if (_length.x - _nowLength.x >= 1.0f) {
		_offset.x += _nowShakeValue.x;
		_nowLength.x += fabs(_nowShakeValue.x);
		flg = true;
	}
	if (_length.y - _nowLength.y >= 1.0f) {
		_offset.y += _nowShakeValue.y;
		_nowLength.y += fabs(_nowShakeValue.y);
		flg = true;
	}
	if (flg) { return false; }

	//�h���ݒ�
	_shakeValue = -_shakeValue;
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//����
	_nowLength = Vector2();
	//�����؂�グ
	if (fabs(_shakeValue.x) < 1.0f && fabs(_shakeValue.y) < 1.0f) {
		_offset = Vector2();
		return true;
	}

	return false;

}