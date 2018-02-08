#include "Player.h"
#include "KeyInput.h"
#include <DxLib.h>
#include "Vector2.h"

#include "Const.h"
#include "Enemy.h"
#include "../House.h"
#include "Collision.h"
#include "EffectManager.h"

Player::Player(const Vector2 pos_)
	:_startPos(pos_),
	_rect(PLAYER_RECT), _vec(Vector2())
{
	_rect.TelePort(pos_);
	if (LoadDivGraph("../image/player.png", (IMG_DIV_CNT_X * IMG_DIV_CNT_Y), IMG_DIV_CNT_X, IMG_DIV_CNT_Y, IMG_SIZE_X, IMG_SIZE_Y, *_handle) == -1)
	{
		printfDx("playerImage�ǂݍ��ݎ��s");
	}
	_weight = 10;
	state = ANI_DEF;
	aniFram = 0;
	aniCnt = 0;
	isDirRight = false;
	_isGround = false;

}


Player::~Player()
{
}

void Player::Update(bool canOperate_) {
    KeyInput& key = KeyInput::GetInstance();
	
	_vec.x = 0.0f;

	Vector2 dir = _vec;
	constexpr float moveSpeed = 5.0f;
	constexpr float jumpPower = 15.0f;
	constexpr float stampPower = 5.0f;
	constexpr float a = 9.8f*(1.0f / 20.0f);
	if (state != ANI_DAMAGE) {
		if (canOperate_) {
			//�ړ�
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) || key.GetKey(KEY_INPUT_LEFT)) {
				dir.x = -moveSpeed;
			}
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) || key.GetKey(KEY_INPUT_RIGHT)) {
				dir.x = moveSpeed;
			}
			if (key.GetKey(KEY_INPUT_D)) {
				dir.x *= 3.0f;
			}
			//�U���i���݂Ԃ�
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) || key.GetKey(KEY_INPUT_DOWN)) {
				dir.y += stampPower;
			}
		}
	}

	
	_rect.Move(dir);
	if (_isGround) {
		dir.y = 0.0f;
	}

	//���肩�甲���Ă�
	if (!_collFlag.CalledConf()) {
		//���������͏c
		if (_collFlag.SideAndBottomHit()) {
			_collFlag.ClearSideAndBottomHitFlag();
		}
	}
	_collFlag.SetPrevCalledFlag();

	//�W�����v
	if (state != ANI_DAMAGE) {
		if (_isGround) {
			if (canOperate_) {
				if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0) || key.GetKey(KEY_INPUT_UP)) {
					dir.y = -jumpPower;
				}
			}
		}
	}
	dir.y += a;
	_vec = dir;

	if (canOperate_) {
		setState(key);	//����key�ɉ�����state��set
	}
	setMove();		//state�ɉ�����aniCnt�̍X�V

}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() - offset_).ToPoint2();
	Point2 n = (_rect.RB() - offset_).ToPoint2();
	Vector2 scalingRatio = Vector2(PLAYER_SIZE / Vector2(IMG_SIZE_X, IMG_SIZE_Y));

	DrawRotaGraph3(s.x + ((n.x - s.x) / 2), s.y + ((n.y - s.y) / 2),
					(IMG_SIZE_X / 2), (IMG_SIZE_Y / 2), scalingRatio.x, scalingRatio.y, (PI * 0),
					_handle[state][aniCnt], true, isDirRight);
	
	aniFram++;

	//pad�ڑ��m�F
	if (GetJoypadNum() == 0)
	{
		printfDx("pad�ڑ��Ȃ�");
	}

}


void Player::setState(KeyInput& key)
{
	//jump�Atample�Adamage���Ɉړ��A�j���[�V�����ɓ��邱�Ɩh�~
	if (state != ANI_JUMP && state != ANI_WEIGH && _isGround && state != ANI_DAMAGE)
	{
		if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0) || key.GetKeyDown(KEY_INPUT_UP))
		{
			state = ANI_JUMP;
			aniFram = 1;
			aniCnt = 0;
		}
		else if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) || key.GetKey(KEY_INPUT_LEFT))
		{
			state = ANI_WALK;
			isDirRight = false;
		}
		else if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) || key.GetKey(KEY_INPUT_RIGHT))
		{
			state = ANI_WALK;
			isDirRight = true;
		}
		else
		{
			state = ANI_DEF;
		}
	}
	else
	{
		//����state��jump�Aweigh�Adamage �A��!_isGround
		 if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) || key.GetKeyDown(KEY_INPUT_DOWN))
		{
			state = ANI_WEIGH;
			aniFram = 1;
			aniCnt = 0;
		}
	}
	
}


void Player::setMove()
{
	switch (state)
	{
	case ANI_DEF:
		aniCnt = 0;
		break;
	case ANI_WALK:
		(aniFram / ANIM_SPEED) % 2 == 1 ? aniCnt = 0: aniCnt = 1;
		break;
	case ANI_WEIGH:
	{
		//���̃A�j���̂����������G�t�F�N�g�o��������
		//������ƊԂ�������
		if (!(aniFram % 5)) {
			EffectManager& em = EffectManager::Instance();
			em.EffectCreate(_rect.Center(), EFFECT_TYPE::EFFECT_TYPE_FALL);
		}
		if (aniFram % ANIM_SPEED * 2 == 0)
		{
			state = ANI_DEF;
		}
		break;
	}
	case ANI_JUMP:
		if (aniFram % ANIM_SPEED == 0)
		{
			aniCnt++;
			if (aniCnt > (IMG_DIV_CNT_X -2))
			{
				state = ANI_DEF;
				aniCnt = 0;
			}
		}
		break;
	case ANI_DAMAGE:
		if (aniFram > (IMG_SIZE_X/2))
		{
			state = ANI_DEF;
		}
		else
		{
			(aniFram / (ANIM_SPEED / 2)) % 2 == 1 ? aniCnt = 0 : aniCnt = 1;
		}
		break;
	case ANI_MAX:
		//���󗈂Ȃ�
		break;
	default:
		break;
	}
}

void Player::OnCollided(const Enemy& enemy_) {

	switch (enemy_.Name()) {
	case EnemyName::NOT_NAME:
		//���ʂł��Ȃ����ł���
		break;
	case EnemyName::NYN:
		
		break;
	case EnemyName::GABYO:
	{
		_collFlag.SetCalledFlag();
		//���������͉����炠�����Ă��Ȃ�I���I
		if (_collFlag.SideAndBottomHit()) {
			return;
		}
		Rect2 ol = Overlap(Rect(), enemy_.Rect());
		//�����擾
		//�ォ��&&�ڒn�Ȃ炢����
		if ((_vec.y > 0.0f && ol.W() > ol.H()) || _vec.y > abs(_vec.x) + 5.0f) {
			if (enemy_.IsGround()) {
				if (state != ANI_DAMAGE) {
					state = ANI_DAMAGE;
					aniFram = 0;
				}
				//�������
				Vector2 n = _rect.Center();
				Vector2 s = enemy_.Pos();
				Vector2 flyVec = (n - s).Normalize() * 15.0f;
				_vec = flyVec;
			}
		}
		else {
			_collFlag.SetSideAndBottomHitFlag();
		}

		break;
	}
	default:
		//���ʂł��Ȃ����ł��B
		break;
	}

}

void Player::OnCollided(const House& house_) {

}