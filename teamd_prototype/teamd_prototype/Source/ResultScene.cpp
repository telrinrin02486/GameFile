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
#include "SoundManager.h"
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
	maskCnt = 0;
	SceneManager::GetInstance().setNextSceneType(SType_GAME);
	SoundManager::GetInstance().PlayLoop(BGM_RESULT);
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
	//game
	if (key.GetKeyUp(KEY_INPUT_UP))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SceneManager::GetInstance().setNextSceneType(SType_GAME);
		SoundManager::GetInstance().Play(BUTTON_1);
	}
	//tutrial
	else if (key.GetKeyUp(KEY_INPUT_DOWN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x + 150,buttomPos2.y + 50 });
		SceneManager::GetInstance().setNextSceneType(SType_TITLE);
		SoundManager::GetInstance().Play(BUTTON_1);
	}

	else if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_RESULT);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getNextSceneType());
	}
	else
	{
		//key入力なし
	}

	maskCnt++;
}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void ResultScene::Draw()
{
	//背景を描画するぜ
	ImageMng::GetInstance()->UiDraw(ID_resultBack, ID_resultButtom2,maskCnt);
	DrawFormatString(250, 250, 0xffffff00, "破壊スコア：%d", SceneManager::GetInstance().GetScore());

}

