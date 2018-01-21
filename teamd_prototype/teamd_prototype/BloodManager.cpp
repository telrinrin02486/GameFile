#include "BloodManager.h"
#include "Blood.h"
#include "Camera.h"

#include <DxLib.h>

BloodManager::BloodManager() {
	Init();
}
int BloodManager::Init() {
	int err = 0;
	_handle = LoadGraph("");
	_radius = 3;

	//‚Æ‚è‚ ‚¦‚¸‚P‚O‚OŒÂ
	_bloods.resize(100);

	return err;
}
int BloodManager::Update() {
	int err = 0;
	for (const auto& blood : _bloods) {
		if (!blood.isAlive) { continue; }



	}
	return err;
}
void BloodManager::Draw(const Camera& camera_) {
	for (const auto& blood : _bloods) {
		if (!blood.isAlive) { continue; }
		
		Point2 offset = (camera_.Offset() + camera_.Pos()).ToPoint2();
		Point2 s = blood.pos - offset;
		Point2 n = Point2(_radius,_radius) - offset;
		DrawExtendGraphF(s.x, s.y, n.x, n.y, _handle, true);
	}
}

void BloodManager::Create(const Point2& point_, const Point2& vec_) {
	//‚±‚±‚ðŒø—¦‚æ‚­‚Å‚«‚ê‚Î

}