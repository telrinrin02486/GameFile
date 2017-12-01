#include "Player.h"
#include "KeyInput.h"
#include <DxLib.h>
#include "Vector2.h"

#include "Const.h"

Player::Player()
	:_startPos(PLAYER_RECT.pos),
	_rect(PLAYER_RECT), _vec(Vector2())
{
	_handle = LoadGraph("../image/leg.png");
	_weight = 10;

}


Player::~Player()
{
}

void Player::Update() {
	KeyInput& key = KeyInput::GetInstance();
	Vector2 dir = Vector2();
	float moveSpeed = 5.0f;
	if (key.GetKey(KEY_INPUT_RETURN)) {
		dir.y += moveSpeed * 3.0f;
	}
	else {
		dir.y -= moveSpeed*2.0f;
	}

	_vec = dir;
	_rect.Move(_vec);

	Vector2& __pos = _rect.pos;
	//‰æ–Ê‚Æ‚Ì“–‚½‚è”»’è‚µ‚Æ‚±(Player‚Ì‰æ–Ê“àˆÚ“®§Œä)
	if (__pos.y < 0.0f) {
		__pos.y = 0.0f;
	}
	if (_rect.Bottom() > static_cast<float>(WINDOW_HEIGHT)) {
		__pos.y = static_cast<float>(WINDOW_HEIGHT) - 
			static_cast<int>(_rect.size.y);
	}

	//


}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();

	DrawExtendGraphF(s.x, s.y, n.x, n.y, _handle, true);


}

void Player::CuddleUp(const Rect2& rect_) {
	//‚Ü‚¸A©g‚Æ‘ÎÛ‚ÌˆÊ’uŠÖŒW’²‚×‚éƒ]
	const Rect2& other = rect_;
	Vector2 distance = other.Center() - _rect.Center();




}