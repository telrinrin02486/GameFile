#pragma once

#include <list>
#include "Vector2.h"
#include "Rect2.h"

//=====================================================================
//						  GameScene.h
//						ゲーム管理クラス
//=====================================================================

//MAX 60秒
#define TIME_MAX 30

class CB_1;
class Player;
class House;
class Enemy;
class EnemyNyn;
class GameScene : public BaseScene
{
private:

	Player		*_player;
	std::list<CB_1*> _cb1List;
	std::list<Enemy*> _enemis;
	std::list<House*> _houses;

	Vector2 _playerStartPos;
	Rect2	_playerInFrame;//プレイヤーを追いかける枠（カメラ用
	Point2 _barrenRange;//初期生成時、敵がわかない範囲
	float _groundPosY;
	bool _prevPlayerGroundFlg;
	int	_crusheCount;

	int _endTime;

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
	int countNumImg[3];
	int startImg;
	int endImg;
	int coronImg;

	void SceneCounter();

	int sceneCun;
	bool SceneStartFlg;
	bool SceneEndFlg;

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