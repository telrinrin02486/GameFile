#include "CB_1.h"

#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include <iostream>

#include "Camera.h"

//乱数の分布がわからん
//確か、randだとばらけた値がでる。
//なめらかな乱数は必要か？
#define MY_RANDOM (rand())
#define HP_RESET ((MY_RANDOM % 400) + 100)

CB_1::CB_1(EffectManager& efm_, float durability_)
	:_efm(efm_),_rect(CB1_RECT), _durability(durability_)
{
	_handle = LoadGraph("../image/yaju.jpg");
	_alive = true;
	_hitPoint = HP_RESET;
}


//CB_1::~CB_1()
//{
//}



int CB_1::Update() {
	int err = 0;

	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		_efm.EffectCreate(Vector2(_rect.Left() + _rect.size.x * 0.5f,
			_rect.Bottom() - 80.0f),EFFECT_TYPE::EFFECT_TYPE_SMOKE);
		_alive = false;
		//地震の使いづらさパない
		Camera::Instance().SetEarthquake(Vector2(15.0f, 0.0f));
	}
	return err;
}

void CB_1::Draw(const Vector2& offset_) {
	Point2 s = (_rect.LT() + offset_).ToPoint2();
	Point2 n = (_rect.RB() + offset_).ToPoint2();

	DrawExtendGraphF(s.x,s.y,n.x,n.y,_handle, true);

}
//壊れちゃうぅ！！
void CB_1::Crushed(const Player& player) {
	//ここ使うだけでメモリ使いすぎぃ！
	//コンパイル時の割り当てだから大丈夫だろうけど、
	//くそスぺだとまずいゾ
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = player.Rect();
	
	Rect2 ol = Overlap(pRect, this->Rect());
	
	//floatの誤差ほんと嫌い
	Vector2 smashedUnit = ol.size / 1000.0f;
	float smashedCorrection = 1.0f - _durability;
	Vector2 smashedValue = smashedUnit * smashedCorrection;
	Vector2 damageVec = player.Vec();
	Vector2 damageNrmVec = damageVec.Normalize();
	damageVec = damageNrmVec;
	damageVec = damageVec * static_cast<float>(player.Weight());
	smashedValue = smashedValue * damageVec;
	int damage = static_cast<int>((damageVec.x + damageVec.y) * smashedCorrection);
	int count = 0;
	//ダメージは縦と横で分けたほうがいいゾ
	while (damage > _hitPoint) {
		damage -= _hitPoint;
		_hitPoint = HP_RESET;
		++count;
	}
	_hitPoint -= damage;
	//つぶす量を計算
	for (int i = 0; i < count; ++i) {
		int r1 = MY_RANDOM;
		int r2 = MY_RANDOM;
		//こ↑こ↓絶対値じゃないとまずいゾ

		Vector2 absSize = ol.size.Absolute();
		Vector2 value = (Vector2(r1, r2) % absSize) * damageNrmVec * 5;
		smashedValue += value;

		//ここでカメラゆらすゾ
		Camera::Instance().SetEarthquake(Vector2(10.0f, 2.0f));
	}
	
	//今Y方向にしかつぶしてないから、
	//X方向の値が見えなかったね。
	_rect.TopCrushed(smashedValue.y);

}
