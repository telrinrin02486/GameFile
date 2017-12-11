#include "Player.h"
#include "KeyInput.h"
#include <DxLib.h>
#include "Vector2.h"

#include "Const.h"

Player::Player()
	:_startPos(PLAYER_RECT.pos),
	_rect(PLAYER_RECT), _vec(Vector2())
{
	LoadDivGraph("../image/player.png", 
		(IMG_DIV_CNT_X * IMG_DIV_CNT_Y), IMG_DIV_CNT_X, IMG_DIV_CNT_Y,
		 IMG_SIZE_X, IMG_SIZE_Y, *_handle);
	_weight = 10;
	state = ANI_MAX;
	aniFram = 0;
	aniCnt = 0;
	isDirRight = false;

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

	setState(key);	//入力keyに応じたstateをset
	setMove();		//stateに応じたaniCntの更新

	
	//画面との当たり判定しとこ
	Vector2& __pos = _rect.pos;
	if (__pos.y < 0.0f) {
		__pos.y = 0.0f;
	}
	if (_rect.Bottom() > static_cast<float>(WINDOW_HEIGHT)) {
		__pos.y = static_cast<float>(WINDOW_HEIGHT) - 
			static_cast<int>(_rect.size.y);
	}

}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();


	DrawRotaGraph3(s.x + ((n.x - s.x) / 2), s.y + ((n.y - s.y) / 2),
					(IMG_SIZE_X / 2), (IMG_SIZE_Y / 2), EXT_RATE_X, EXT_RATE_Y, (PI * 0),
					_handle[state][aniCnt], true, isDirRight);
	aniFram++;
}

void Player::CuddleUp(const Rect2& rect_) {

	//まず、自身と対象の位置関係調べるゾ
	const Rect2& other = rect_;
	Vector2 distance = other.Center() - _rect.Center();
}

void Player::setState(KeyInput& key)
{
	//jump、tample中に移動アニメーションに入ること防止
	if (state != ANI_TAMPLE && state != ANI_JUMP)
	{
		if (key.GetKeyDown(KEY_INPUT_SPACE))
		{
			state = ANI_JUMP;
			aniFram = 0;
		}
		else if (key.GetKeyDown(KEY_INPUT_DOWN))
		{
			state = ANI_TAMPLE;
			aniFram = 0;
		}
		else if (key.GetKey(KEY_INPUT_LEFT))
		{
			state = ANI_WALK;
			isDirRight = false;
		}
		else if (key.GetKey(KEY_INPUT_RIGHT))
		{
			state = ANI_WALK;
			isDirRight = true;
		}
		else
		{
			state = ANI_MAX;
		}
	}
	
}

void Player::setMove()
{
	switch (state)
	{
	case ANI_WALK:
		(aniFram / ANIM_SPEED) % 2 == 1 ? aniCnt = 0: aniCnt = 1;
		break;
	case ANI_TAMPLE:
		if (aniFram % ANIM_SPEED == 0)
		{
			aniCnt++;
			if (aniCnt > IMG_DIV_CNT_X)
			{
				state = ANI_MAX;
				aniCnt = 0;
			}
		}
		break;
	case ANI_JUMP:
		if (aniFram % ANIM_SPEED == 0)
		{
			aniCnt++;
			if (aniCnt > IMG_DIV_CNT_X)
			{
				state = ANI_MAX;
				aniCnt = 0;
			}
		}
		break;
	case ANI_MAX:
		aniCnt = 0;
		break;
	default:
		break;
	}
}
