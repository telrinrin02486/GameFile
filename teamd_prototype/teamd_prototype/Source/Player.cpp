#include "Player.h"
#include "KeyInput.h"
#include <DxLib.h>
#include "Vector2.h"

#include "Const.h"
#include "Enemy.h"
#include "../House.h"

Player::Player()
	:_startPos(PLAYER_RECT.LT()),
	_rect(PLAYER_RECT), _vec(Vector2())
{
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

void Player::Update() {
    KeyInput& key = KeyInput::GetInstance();
	
	_vec.x = 0.0f;

	Vector2 dir = _vec;
	constexpr float moveSpeed = 5.0f;
	constexpr float jumpPower = 20.0f;
	constexpr float stampPower = 15.0f;
	constexpr float a = 9.8f*(1.0f / 10.0f);
	if (state != ANI_DAMAGE) {
		//移動
		if (key.GetKey(KEY_INPUT_LEFT)) {
			dir.x = -moveSpeed;
		}
		if (key.GetKey(KEY_INPUT_RIGHT)) {
			dir.x = moveSpeed;
		}
		if (key.GetKey(KEY_INPUT_D)) {
			dir.x *= 3.0f;
		}
		//攻撃（踏みつぶし
		if (key.GetKey(KEY_INPUT_DOWN)) {
			dir.y += stampPower;
		}
	}

	_rect.Move(dir);
	if (_isGround) {
		dir.y = 0.0f;
	}
	//ジャンプ
	if (state != ANI_DAMAGE) {
		if (_isGround) {
			if (key.GetKey(KEY_INPUT_UP)) {
				dir.y = -jumpPower;
			}
		}
	}
	dir.y += a;
	_vec = dir;

	setState(key);	//入力keyに応じたstateをset
	setMove();		//stateに応じたaniCntの更新

}

void Player::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() - offset_).ToPoint2();
	Point2 n = (_rect.RB() - offset_).ToPoint2();


	DrawRotaGraph3(s.x + ((n.x - s.x) / 2), s.y + ((n.y - s.y) / 2),
					(IMG_SIZE_X / 2), (IMG_SIZE_Y / 2), EXT_RATE_X, EXT_RATE_Y, (PI * 0),
					_handle[state][aniCnt], true, isDirRight);
	//DrawBox(s.x, s.y, n.x, n.y, 0xffffffff, false);
	aniFram++;
	DrawFormatString(s.x, s.y - 15, 0xffffffff, "weight:%d", _weight);

}


void Player::setState(KeyInput& key)
{
	//jump、tample、damage中に移動アニメーションに入ること防止
	if (state != ANI_WEIGH && _isGround && state != ANI_DAMAGE)
	{
		if (key.GetKeyDown(KEY_INPUT_UP))
		{
			state = ANI_JUMP;
			aniFram = 1;
			aniCnt = 0;
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
		else if (key.GetKey(KEY_INPUT_SPACE))
		{
			state = ANI_DAMAGE;
			aniFram = 0;
		}
		else
		{
			state = ANI_DEF;
		}
	}
	else
	{
		//のしかかりアニメーションをしない時がある
		//見た感じisGround自体が地面と判定を取っているのではなく
		//jumpアニメーションが終わればisGroundをtrueにしていると思われる
		//なお自分の実装ではないため質問しなければわからない
		//現在stateがjump、weigh、damage 、か!_isGround
		 if (key.GetKeyDown(KEY_INPUT_DOWN)/* && state == ANI_JUMP*/)
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
		if (aniFram % ANIM_SPEED*2 == 0)
		{
			state = ANI_DEF;
		}
		break;
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
		if (state != ANI_DAMAGE) {
			state = ANI_DAMAGE;
			aniFram = 0;
		}
		//吹き飛び
		Vector2 n = _rect.Center();
		Vector2 s = enemy_.Pos();
		Vector2 flyVec = (n - s).Normalize() * 10.0f;
		_vec = flyVec;
		break;
	}
	default:
		//識別できない方です。
		break;
	}

}

void Player::OnCollided(const House& house_) {

}