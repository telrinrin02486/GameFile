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

//更新
void Camera::Update() {
	//シェイク
	if (_shakeFuncPtr != nullptr) {
		_state = Camera::Earthquake;
		if ((this->*_shakeFuncPtr)()) {
			_state = Camera::Idel;
			_shakeFuncPtr = nullptr;
		}
	}

}

//現在地から移動
void Camera::Move(float dirX_, float dirY_) {
	_pos += Vector2(dirX_, dirY_);

}
void Camera::Move(const Vector2& dir_) {
	_pos += dir_;

}
//テレポート
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

	//揺れ値の調整
	_shakeValue = -(_shakeValue - (_shakeValue * _reductionRate));
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),fabs(_shakeValue.y) + fabs(_offset.y));//長さ
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

	//揺れを設定
	_shakeValue = -_shakeValue;
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//長さ
	_nowLength = Vector2();

	_shakeFuncPtr = &Camera::ShakeForever;
}

void Camera::StopEarthquake() {
	_offset = Vector2();
	_shakeFuncPtr = nullptr;

}


//このシェイクは揺れを実装してるが、
//余韻だったり、なめらかな揺れは対応していない。
//戻り値：関数ポインタを○○　true:消して！　false:そのまましといて
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

	//揺れを設定
	_shakeValue = -(_shakeValue - (_shakeValue * _reductionRate));
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//長さ
	_nowLength = Vector2();
	//処理切り上げ
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

	//揺れを設定
	_shakeValue = -_shakeValue;
	_nowShakeValue = _shakeValue * _shakeSpeed;
	_length = Vector2(fabs(_shakeValue.x) + fabs(_offset.x),
		fabs(_shakeValue.y) + fabs(_offset.y));//長さ
	_nowLength = Vector2();
	//処理切り上げ
	if (fabs(_shakeValue.x) < 1.0f && fabs(_shakeValue.y) < 1.0f) {
		_offset = Vector2();
		return true;
	}

	return false;

}