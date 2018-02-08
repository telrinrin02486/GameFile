#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  TutrialScene.h
//						チュートリアル管理クラス
//=====================================================================

//MAX 60秒
#define TIME_MAX 60

class CB_1;
class Player;
class House;
class EnemyNyn;
class TutrialScene : public BaseScene
{
private:

	Player		*_player;
	House		*house;
	int uiID;
	bool tutFlag;

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//プレイヤーを追いかける枠（カメラ用

	float _groundPosY;
	bool _prevPlayerGroundFlg;

	int _minLimit, _maxLimit;

	int nowPad, oldPad;


public:
	TutrialScene();	//コンストラクタ
	~TutrialScene();	//デストラクタ

					//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画
	void modul1();
	void modul2();
	void modul3();
	void modul4();
	void modul5();
	void textDraw(int id);
};