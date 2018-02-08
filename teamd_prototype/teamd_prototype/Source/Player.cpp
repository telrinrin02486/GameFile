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
		printfDx("playerImage読み込み失敗");
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
			//移動
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) || key.GetKey(KEY_INPUT_LEFT)) {
				dir.x = -moveSpeed;
			}
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) || key.GetKey(KEY_INPUT_RIGHT)) {
				dir.x = moveSpeed;
			}
			if (key.GetKey(KEY_INPUT_D)) {
				dir.x *= 3.0f;
			}
			//攻撃（踏みつぶし
			if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) || key.GetKey(KEY_INPUT_DOWN)) {
				dir.y += stampPower;
			}
		}
	}

	
	_rect.Move(dir);
	if (_isGround) {
		dir.y = 0.0f;
	}

	//判定から抜けてる
	if (!_collFlag.CalledConf()) {
		//横もしくは縦
		if (_collFlag.SideAndBottomHit()) {
			_collFlag.ClearSideAndBottomHitFlag();
		}
	}
	_collFlag.SetPrevCalledFlag();

	//ジャンプ
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
		setState(key);	//入力keyに応じたstateをset
	}
	setMove();		//stateに応じたaniCntの更新

}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() - offset_).ToPoint2();
	Point2 n = (_rect.RB() - offset_).ToPoint2();
	Vector2 scalingRatio = Vector2(PLAYER_SIZE / Vector2(IMG_SIZE_X, IMG_SIZE_Y));

	DrawRotaGraph3(s.x + ((n.x - s.x) / 2), s.y + ((n.y - s.y) / 2),
					(IMG_SIZE_X / 2), (IMG_SIZE_Y / 2), scalingRatio.x, scalingRatio.y, (PI * 0),
					_handle[state][aniCnt], true, isDirRight);
	
	aniFram++;

	//pad接続確認
	if (GetJoypadNum() == 0)
	{
		printfDx("pad接続なし");
	}

}


void Player::setState(KeyInput& key)
{
	//jump、tample、damage中に移動アニメーションに入ること防止
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
		//現在stateがjump、weigh、damage 、か!_isGround
		 if ((((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) || key.GetKeyDown(KEY_INPUT_DOWN)) && !_isGround)
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
		//このアニメのあいだ落下エフェクト出し続ける
		//ちょっと間をあける
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
		//現状来ない
		break;
	default:
		break;
	}
}

void Player::OnCollided(const Enemy& enemy_) {

	switch (enemy_.Name()) {
	case EnemyName::NOT_NAME:
		//識別できない方ですね
		break;
	case EnemyName::NYN:
		
		break;
	case EnemyName::GABYO:
	{
		_collFlag.SetCalledFlag();
		//横もしくは下からあたってたなら終わり！
		if (_collFlag.SideAndBottomHit()) {
			return;
		}
		Rect2 ol = Overlap(Rect(), enemy_.Rect());
		//方向取得
		//上から&&接地ならいたい
		if ((_vec.y > 0.0f && ol.W() > ol.H()) || _vec.y > abs(_vec.x) + 5.0f) {
			if (enemy_.IsGround()) {
				if (state != ANI_DAMAGE) {
					state = ANI_DAMAGE;
					aniFram = 0;
				}
				//吹き飛び
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
		//識別できない方です。
		break;
	}

}

void Player::OnCollided(const House& house_) {

}