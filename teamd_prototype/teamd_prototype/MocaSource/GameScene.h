#pragma once

#include "Vector2.h"
#include "Rect2.h"
//=====================================================================
//						  GameScene.h
//						ゲーム管理クラス
//=====================================================================

class CB_1;
class Player;
class EnemyManager;
class GameScene : public BaseScene
{
private:
	EffectManager	*_effectManager;

	CB_1		*_cb;
	Player		*_player;

	EnemyManager *_EM;//追記

	Vector2 _playerStartPos;
	Rect2 _cbStartRect;

public:
	GameScene();	//コンストラクタ
	~GameScene();	//　デストラクタ

	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

	//　アクセサ-----------------------------------------------------------
	EffectManager	*GetEffectMng()	{ return _effectManager; }
};