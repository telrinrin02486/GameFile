#include "NormalHuman.h"

#include "DxLib.h"


NormalHuman::NormalHuman(const Player& player_)
	:_player(player_)
{

}


NormalHuman::~NormalHuman()
{
}

int NormalHuman::Update() {
	int err = 0;

	constexpr float gravity = 8.2f * (1.0f / 20.0f);
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	int err = 0;
	//ˆÚ“®
	if (_count++ > 50) {
		_count = 0;
		_dirx = -_dirx;
	}

	_vec.x = _dirx;
	_vec.y += gravity;
	_rect.Move(_vec);
	//•ûŒüî•ñ
	if (_dirx < 0) {
		_isRightDir = false;
	}
	else {
		_isRightDir = true;
	}


	return err;
}
void NormalHuman::Draw(const Camera& camera_) const {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();

	DrawExtendGraphF(s.x, s.y, n.x, n.y, _handle, true);

}
bool NormalHuman::IsAlive() const {
	return _isAlive;
}