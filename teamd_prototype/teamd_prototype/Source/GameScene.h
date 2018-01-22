#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  GameScene.h
//						ゲーム管理クラス
//=====================================================================

//MAX 60秒
#define TIME_MAX 60

class CB_1;
class Player;
class House;
class EnemyNyn;
class GameScene : public BaseScene
{
private:

	Player		*_player;
	std::list<CB_1*> _cb1List;
	std::list<EnemyNyn*> _nyns;
	std::list<House*> _houses;

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//プレイヤーを追いかける枠（カメラ用

	float _groundPosY;
	bool _prevPlayerGroundFlg;
	int	_crusheCount;

	int _minLimit, _maxLimit;

	//開始時間
	unsigned int timeStart;
	//経過時間
	unsigned int timeCun;

	void TimeCunter();

	//変更●-----
	int scoreImg;
	int timeImg;
	int numImg[10];
	int coronImg;
	//----------

public:
	GameScene();	//コンストラクタ
	~GameScene();	//デストラクタ

	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

};