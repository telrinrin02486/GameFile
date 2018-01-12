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

class GameScene : public BaseScene
{
private:

	Player		*_player;
	std::list<CB_1*> _cb1List;

	Vector2 _playerStartPos;

	const Rect2 _ground;
	bool _prevPlayerGroundFlg;
	int	_crusheCount;

	//開始時間
	unsigned int timeStart;
	//経過時間
	unsigned int timeCun;

	void TimeCunter();

	

public:
	GameScene();	//コンストラクタ
	~GameScene();	//デストラクタ

	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

};