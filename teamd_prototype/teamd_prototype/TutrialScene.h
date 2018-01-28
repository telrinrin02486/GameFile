#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  TutrialScene.h
//						ゲーム管理クラス
//=====================================================================

//MAX 60秒
#define TIME_MAX 60

class CB_1;
class Player;
class EnemyNyn;
class TutrialScene : public BaseScene
{
private:

	Player	*_player;
	EnemyNyn *enemy;
	

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//プレイヤーを追いかける枠（カメラ用

	float _groundPosY;
	bool _prevPlayerGroundFlg;

	int _minLimit, _maxLimit;



public:
	TutrialScene();	//コンストラクタ
	~TutrialScene();	//デストラクタ

					//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

};