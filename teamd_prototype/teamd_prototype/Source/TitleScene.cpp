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
	titleImage	= LoadGraph("../image/UI/title/titleImage.png");
	startButtom = LoadGraph("../image/UI/title/startButtom.png");
	backImg		= LoadGraph("../image/title.png");

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
	DrawGraph(1080 / 2, 480 / 3, titleImage, true);
	DrawGraph(1080 / 2, 480 / 2, startButtom, true);
	DrawGraph(0, 0, backImg, false);
	DxLib::DrawGraph(0, 0, _texID, false);	//背景
	
}
