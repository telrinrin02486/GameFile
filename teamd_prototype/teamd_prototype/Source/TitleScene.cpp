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
	SoundManager::GetInstance().Play(BGM_TITLE);
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
	SoundManager::GetInstance().Play(BGM_TITLE);
	bool i = SoundManager::GetInstance().PlayCheak(BGM_TITLE);
	KeyInput& key = KeyInput::GetInstance();
	//key入力でmaskのposをset
	//maskの状態でtitl or tutrialへの遷移
	//遷移する予定のシーンを変数で管理
	if (key.GetKeyUp(KEY_INPUT_UP))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_GAME);
	}

	//まだ存在しないので
	//isScene == SType_TUTORIALの状態で
	//ENTER押さないでね
	if (key.GetKeyUp(KEY_INPUT_DOWN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x + 150,buttomPos2.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_TUTRIAL);
	}
	

	//titleへ
	if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getSceneType());
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_TITLE);
	}
	maskCnt++;
	//SoundManager::GetInstance().Play(BGM_TITLE);
}

//---------------------------------------------------------------------
//　描画
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	//背景を描画するぜ
	ImageMng::GetInstance()->UiDraw(ID_titleBack, ID_tutorialButtom, maskCnt);


}


