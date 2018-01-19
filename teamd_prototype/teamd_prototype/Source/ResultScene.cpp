//=====================================================================
//						  ResultScene.cpp
//						ゲーム管理クラス
//=====================================================================
using namespace std;

// ResultScene.h
#include "BaseScene.h"
#include "Vector2.h"		// 使用なし
#include "ResultScene.h"	// BaseScene、EffectManager

// ResultScene.cpp
#include "KeyInput.h"		
#include "DxLib.h"
#include "SceneManager.h"



//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
ResultScene::ResultScene()
{
}


//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
ResultScene::~ResultScene()
{
}

//---------------------------------------------------------------------
//　初期化
//---------------------------------------------------------------------
void ResultScene::Initialize()
{

	//シーン切り替えフラグ
	_isChange = false;

	//背景画像をロード
	resultButtom1 = LoadGraph("../image/UI/result/resultButtom1.png");
	resultButtom2 = LoadGraph("../image/UI/result/resultButtom2.png");
	backImg		  = LoadGraph("../image/result.png");

}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void ResultScene::Finalize()
{
	//各種開放


}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void ResultScene::Update()
{
	KeyInput& key = KeyInput::GetInstance();
	//titleへ
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_TITLE);
	}
	//gameへ
	if (key.GetKeyUp(KEY_INPUT_3))
	{
		SceneManager::GetInstance().ChangeScene(SType_GAME);
	}


}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void ResultScene::Draw()
{
	//背景を描画するぜ
	DrawGraph(1080 / 2, 480 / 3, resultButtom1, true);
	DrawGraph(1080 / 2, 480 / 2, resultButtom2, true);
	//DrawGraph(0, 0, backImg, false);
	DxLib::DrawGraph(0, 0, _texID, false);	//背景
	DrawFormatString(250, 250, 0xffffff00, "破壊スコア：%d", SceneManager::GetInstance().GetScore());

}
