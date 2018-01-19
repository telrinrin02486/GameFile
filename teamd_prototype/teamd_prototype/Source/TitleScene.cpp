//=====================================================================
//						  TitleScene.cpp
//						ゲーム管理クラス
//=====================================================================
using namespace std;

// TitleScene.h
#include "BaseScene.h"
#include "Vector2.h"		// 使用なし
#include "TitleScene.h"		// BaseScene、EffectManager

// TitleScene.cpp
#include "KeyInput.h"		// 使用なし
#include "DxLib.h"
#include "SceneManager.h"





//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
TitleScene::TitleScene()
{
}


//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------------------
//　初期化
//---------------------------------------------------------------------
void TitleScene::Initialize()
{
	
	//シーン切り替えフラグ
	_isChange = false;

	//背景画像をロード
	titleImage[ID_title]		= LoadGraph("../image/UI/title/titleImage.png");
	titleImage[ID_startButtom]	= LoadGraph("../image/UI/title/startButtom.png");
	titleImage[ID_titleBack]	= LoadGraph("../image/sceneBack/title/titleBack.png");

}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void TitleScene::Finalize()
{
	//各種開放

	
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void TitleScene::Update()
{
	
	KeyInput& key = KeyInput::GetInstance();
	//titleへ
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_GAME);
	}
	
}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	//背景を描画するぜ
	DrawGraph(0, 0, titleImage[ID_titleBack], false);
	DrawGraph(400, 480 / 5, titleImage[ID_title], true);
	DrawGraph(475, 480 / 2, titleImage[ID_startButtom], true);
	
}

