#include "CB_1.h"

#include <DxLib.h>
#include <math.h>
#include "Player.h"
#include "Collision.h"

#include "Const.h"

#include "EffectManager.h"

#include <iostream>

#include "Camera.h"


#define MY_RANDOM (rand())
#define HP_RESET(x) ((MY_RANDOM % x))

constexpr char* const imgPaths[] = {
	"../image/humen/boy1.png",
	"../image/humen/boy2.png",
	"../image/humen/boy3.png",
	"../image/humen/boy4.png",
};

CB_1::CB_1(const Rect2& rect_)
	:_rect(rect_){
	//矩形がクラスなために、こういうときにめんどくさい。
	//クラスが悪いんじゃなく、設計が悪いんだけどね？
	Init(rect_);

}


//CB_1::~CB_1()
//{
//}


void CB_1::Init(const Rect2& rect_) {
	_rect = rect_;
	_maxHitPoint = static_cast<unsigned int>(((_rect.Size().x + _rect.Size().y)*0.5f)*1.5f);
	_hitPoint = HP_RESET(_maxHitPoint);
	_durability = 0.5f;
	unsigned int r = rand() % 4;
	_handle = LoadGraph(imgPaths[r]);
	_alive = true;
	_vec = Vector2();
	_count = 0;
	_dirx = 2.0f;
	_isRightDir = true;
	_isGround = false;
}
int CB_1::Update() {
	EffectManager& efm = EffectManager::Instance();
	constexpr float gravity = 8.2f * (1.0f / 20.0f);
	_vec.x = 0.0f;
	if (_isGround) {
		_vec.y = 0.0f;
	}
	int err = 0;
	//移動
	if (_count++ > 50) {
		_count = 0;
		_dirx = -_dirx;
	}

	_vec.x = _dirx;
	_vec.y += gravity;
	_rect.Move(_vec);
	//方向情報
	if (_dirx < 0) {
		_isRightDir = false;
	}
	else {
		_isRightDir = true;
	}

	//死亡＆エフェクト
	if (_alive && (_rect.Bottom() - _rect.Top()) < 10.0f) {
		efm.EffectCreate(Vector2(_rect.Left() + _rect.Size().x * 0.5f,
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
	const Rect2 rect = player.Rect();//相手方の矩形
	const Vector2 vec = player.Vec();//力の方向
	if (_durability >= 1.0f) {
		return;
	}
	const Rect2 pRect = rect;
	
	Rect2 ol = Overlap(pRect, this->Rect());
	
	//floatの誤差ほんと嫌い
	Vector2 smashedUnit = ol.Size() / 1000.0f;
	float smashedCorrection = 1.0f - _durability;
	Vector2 smashedValue = smashedUnit * smashedCorrection;
	//速度だけでいいかなぁ。
	Vector2 damageVec = vec;
	Vector2 damageNrmVec = damageVec.Normalize();
	damageVec = damageNrmVec;
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

		//ここでカメラゆらすゾ
		Camera::Instance().SetEarthquake(Vector2(10.0f, 2.0f));
	}

	//本来つぶれるには
	//自身の硬さとか、勢いとかいろいろいるゾ
	//この辺りはどうするゾ～？

	_rect.TopCrushed(smashedValue.y);




}
