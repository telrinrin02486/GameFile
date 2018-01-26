#include "BloodManager.h"
#include "Blood.h"
#include "Camera.h"
#include "Collision.h"
#include "Rect2.h"

#include <DxLib.h>

BloodManager::BloodManager() {
	Init();
}
int BloodManager::Init() {
	int err = 0;
	_handle = LoadGraph("../image/blood.png");
	_radius = 20;

	return err;
}
int BloodManager::Update() {
	Camera& camera = Camera::Instance();
	int err = 0;
	auto it = _bloods.begin();
	for (; it != _bloods.end();) {
		Rect2 window = { camera.Pos() + camera.Offset(),camera.WindowSize() };
		Rect2 myRect = { it->_pos, Vector2(_radius,_radius) };
		if (!IsHit(window,myRect)) {
			it = _bloods.erase(it);
			continue;
		}
		BloodUpdate(*it);
		++it;
	}
	return err;
}
void BloodManager::Draw(const Camera& camera_) {
	for (const auto& blood : _bloods) {
		if (!blood._isAlive) { continue; }
		BloodDraw(blood, camera_);
	}
}

void BloodManager::Create(const Vector2& pos_, const Vector2& vec_) {
	//‚±‚±‚ðŒø—¦‚æ‚­‚Å‚«‚ê‚Î
	_bloods.push_back(Blood(pos_, vec_));
}
int BloodManager::BloodUpdate(Blood& blood_) {
	int err = 0;
	constexpr float gravity = 9.8f * (1.0f / 30.0f);
	if (blood_._isGround) {
		blood_._vec = Vector2::ZERO;
		blood_._isAlive = false;//Ž€
	}
	blood_._pos += blood_._vec;
	blood_._vec.y += gravity;

	return err;
}
void BloodManager::BloodDraw(const Blood& blood_, const Camera& camera_) {
	Point2 offset = (camera_.Offset() + camera_.Pos()).ToPoint2();
	Point2 s = blood_._pos.ToPoint2() - offset;
	Point2 n = blood_._pos.ToPoint2() + Point2(_radius, _radius) - offset;
	DrawExtendGraphF(s.x, s.y, n.x, n.y, _handle, true);

}