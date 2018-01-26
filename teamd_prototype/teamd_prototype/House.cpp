#include "House.h"
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include <iostream>
#include <string>
#include "Camera.h"
#include <cmath>
#include <DxLib.h>
#include "ImageMng.h"

#define MY_RANDOM (rand())
#define HP_RESET(x) ((MY_RANDOM % x))

//↓ポインタを固定したら怒られるンゴ
const std::string ImagePaths[] = {
	"../image/building2.png",
};
const Vector2 ImageSize[] = {
	Vector2( 100,100 ),
};
//確かにRectはわかりづらいなぁ。
//考えてみれば画像はサイズがわかればいいしなぁ。

House::House(const Vector2& pos_)
	:_rect(pos_, Vector2(600, 600)) {
	ImageMng* imageMng = ImageMng::GetInstance();
	_maxHitPoint = static_cast<unsigned int>((MY_RANDOM % 300) + 100);
	_hitPoint = HP_RESET(_maxHitPoint);
	_durability = 0.5f;
	int r = rand() % sizeof(ImagePaths) / sizeof(std::string);
	_handle = LoadGraph(ImagePaths[r].c_str());//画像ハンドル取得
	_rect.ReSize(ImageSize[r]);
	_alive = true;
	_vec = Vector2();
	_count = 0;
	_isGround = false;
}


House::~House()
{
}


int House::Update() {
	int err = 0;
	EffectManager& efm = EffectManager::Instance();
	//重力加速度間違えてた・・・ﾊｽﾞｶﾋﾟ
	constexpr float gravity = 9.8f * (1.0f / 20.0f);
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	//動きを対応させた後で重力付けとかないといけない？
	_rect.Move(_vec);
	_vec.y += gravity;
	//前フレームで当たり判定処理を行った。
	if (!_collFlag.CalledConf()) {
		//横から当たってる？
		if (_collFlag.SideHit()) {
			_collFlag.ClearSideHitFlag();
		}
		//縦から当たってる？
		if (_collFlag.VerticalHit()) {
			_collFlag.ClearVerticalHitFlag();
		}
	}
	//前状態を保存
	_collFlag.SetPrevCalledFlag();
	//死亡＆エフェクト
	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		efm.EffectCreate(Vector2(_rect.Left() + _rect.Size().x * 0.5f,
			_rect.Bottom() - 80.0f), EFFECT_TYPE::EFFECT_TYPE_SMOKE);
		_alive = false;
		//地震の使いづらさパない
		Camera::Instance().SetEarthquake(Vector2(15.0f, 0.0f));
	}
	return err;
}
void House::Draw(const Camera& camera_) {
	Vector2 offset = camera_.Offset() + camera_.Pos();
	Point2 s = (_rect.LT() - offset).ToPoint2();
	Point2 n = (_rect.RB() - offset).ToPoint2();

	DrawExtendGraphF(s.x, s.y, n.x, n.y, _handle, true);

	//unsigned int color = 0x00000000;
	//if (_collFlag.SideHit()) {
	//	color |= 0x00ff00ff;
	//	DrawString(s.x, s.y - 15, "Side", color);
	//}
	//if (_collFlag.VerticalHit()) {
	//	color |= 0xff0000ff;
	//	DrawString(s.x, s.y - 15, "Vertical", color);
	//}
	//if (_collFlag.CalledConf()) {
	//	DrawString(s.x, s.y - 30, "Called", color);
	//}
	//DrawBox(s.x, s.y, n.x, n.y, color, false);

}
//壊れちゃうぅ！！
void House::Crushed(const Player& player) {
	const Rect2 rect = player.Rect();//相手方の矩形
	const Vector2 vec = player.Vec();//力の方向
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = rect;

	Rect2 ol = Overlap(pRect, _rect);

	//floatの誤差ほんと嫌い
	Vector2 smashedUnit = ol.Size() / 1000.0f;
	float smashedCorrection = 1.0f - _durability;
	Vector2 smashedValue = smashedUnit * smashedCorrection;
	//速度だけでいいかなぁ。
	Vector2 damageVec = vec;
	Vector2 damageNrmVec = damageVec.Normalize();
	//damageVec = damageNrmVec;
	damageVec = damageVec * static_cast<float>(player.Weight());
	smashedValue = smashedValue * damageVec;
	int damage = static_cast<int>((damageVec.x + damageVec.y) * smashedCorrection);
	int count = 0;
	//ダメージは縦と横で分けたほうがいいゾ
	while (damage > _hitPoint) {
		damage -= _hitPoint;
		_hitPoint = HP_RESET(_maxHitPoint);
		++count;
	}
	_hitPoint -= damage;
	//つぶす量を計算
	for (int i = 0; i < count; ++i) {
		int r1 = MY_RANDOM;
		int r2 = MY_RANDOM;
		//こ↑こ↓絶対値じゃないとまずいゾ
		Vector2 absSize = ol.Size().Absolute();
		Vector2 value = (Vector2(r1, r2) % absSize) * damageNrmVec * 5;
		smashedValue += value;


	}
	_rect.TopCrushed(smashedValue.y);



}

void House::OnCollided(const Player& player_) {
	//要件：横から当たったなら、当たらなくなるまで触れなくしてほしい
	//呼ばれたらチェックする
	_collFlag.SetCalledFlag();
	//横から当たってることになってるなら
	if (_collFlag.SideHit()) {
		_collFlag.ClearVerticalHitFlag();
		return;
	}
	//縦から当たってることになってるなら
	if (_collFlag.VerticalHit()) {
		_collFlag.ClearSideHitFlag();
	}

	Rect2 ol = Overlap(player_.Rect(), _rect);
	//横から当たってきたなら
	if (ol.W() < ol.H()) {
		_collFlag.SetSideHitFlag();
	}
	//縦なら
	else {
		_collFlag.SetVerticalHitFlag();
		//つぶす
		Crushed(player_);
	}

}
void House::OnCollided(const Enemy& enemy_) {

}
