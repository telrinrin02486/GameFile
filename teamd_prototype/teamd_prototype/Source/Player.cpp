#include "Player.h"
#include "KeyInput.h"
#include <DxLib.h>
#include "Vector2.h"

#include "Const.h"



Player::Player()
	:_startPos(PLAYER_RECT.LT()),
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
	_isGround = false;

}


Player::~Player()
{
}

void Player::Update() {
    KeyInput& key = KeyInput::GetInstance();
	
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	Vector2 dir = _vec;
	constexpr float moveSpeed = 5.0f;
	constexpr float jumpPower = 7.0f;
	constexpr float stampPower = 15.0f;
	constexpr float a = 8.2f*(1.0f / 20.0f);
	//�ړ�
	if (key.GetKey(KEY_INPUT_LEFT)) {
		dir.x = -moveSpeed;
	}
	if (key.GetKey(KEY_INPUT_RIGHT)) {
		dir.x = moveSpeed;
	}
	if (key.GetKey(KEY_INPUT_UP)) {
		dir.y = -jumpPower;
	}
	//�U���i���݂Ԃ�
	if (key.GetKey(KEY_INPUT_DOWN)) {
		dir.y += stampPower;
	}
	dir.y += a;

	_vec = dir;
	_rect.Move(_vec);

	setState(key);	//����key�ɉ�����state��set
	setMove();		//state�ɉ�����aniCnt�̍X�V

}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();


	DrawRotaGraph3(s.x + ((n.x - s.x) / 2), s.y + ((n.y - s.y) / 2),
					(IMG_SIZE_X / 2), (IMG_SIZE_Y / 2), EXT_RATE_X, EXT_RATE_Y, (PI * 0),
					_handle[state][aniCnt], true, isDirRight);
	DrawBox(s.x, s.y, n.x, n.y, 0xffffffff, false);
	aniFram++;
}


void Player::setState(KeyInput& key)
{
	//jump�Atample���Ɉړ��A�j���[�V�����ɓ��邱�Ɩh�~
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
