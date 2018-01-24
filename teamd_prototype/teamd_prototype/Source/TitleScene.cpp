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
#include "SoundManager.h"
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
	maskCnt = 0;
	SceneManager::GetInstance().setSceneType(SType_GAME);
	SoundManager::GetInstance().PlayLoop(BGM_TITLE);
}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void TitleScene::Finalize()
{
}

//---------------------------------------------------------------------
//　更新
//---------------------------------------------------------------------
void TitleScene::Update()
{
	
	KeyInput& key = KeyInput::GetInstance();
	//game
	if (key.GetKeyUp(KEY_INPUT_UP))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_GAME);
		SoundManager::GetInstance().Play(BUTTON_1);
	}
	//tutrial
	else if (key.GetKeyUp(KEY_INPUT_DOWN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x + 150,buttomPos2.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_TUTRIAL);
		SoundManager::GetInstance().Play(BUTTON_1);
	}
	
	else if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_TITLE);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getSceneType());
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
void TitleScene::Draw()
{
	//背景を描画するぜ
	ImageMng::GetInstance()->UiDraw(ID_titleBack, ID_tutorialButtom, maskCnt);
}


