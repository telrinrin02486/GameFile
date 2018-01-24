//===================================================================
//						SceneManager.cpp
//						シーン管理クラス
//===================================================================
using namespace std;

// SceneManager.h
#include "BaseScene.h"
#include "Vector2.h"			// 使用なし
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect、Vector2、std
#include "TitleScene.h"	
#include "../TutrialScene.h"	
#include "GameScene.h"			// BaseScene、EffectManager
#include "ResultScene.h"	
#include "SceneManager.h"		// BaseScene

//SceneManager.cpp

//-------------------------------------------------------------------
//　コンストラクタ
//-------------------------------------------------------------------
SceneManager::SceneManager()
{

}

//-------------------------------------------------------------------
//　デストラクタ
//-------------------------------------------------------------------
SceneManager::~SceneManager()
{

}

//-------------------------------------------------------------------
//　初期化
//-------------------------------------------------------------------
void SceneManager::Initialize()
{
	
	//titleからの遷移がわずらわしければ
	//ココの生成をgameに変えて
	_scene = new TitleScene();
	_st = SType_TITLE;
	_scene->Initialize();
}

//-------------------------------------------------------------------
//　終了処理
//-------------------------------------------------------------------
void SceneManager::Finalize()
{

}

//-------------------------------------------------------------------
//　更新
//-------------------------------------------------------------------
void SceneManager::Update()
{
	_scene->Update();
}

//-------------------------------------------------------------------
//　描画
//-------------------------------------------------------------------
void SceneManager::Draw()
{
	_scene->Draw();
}

//-------------------------------------------------------------------
//　シーン切り替え
//-------------------------------------------------------------------
void SceneManager::ChangeScene( SCENE_TYPE st )
{
	if ( _scene )
	{
		delete( _scene );
		_scene = nullptr;
	}

	switch ( st )
	{
	case SType_TITLE:
		_scene = new TitleScene();
		_st = SType_TITLE;
		_scene->Initialize();
		break;
	case SType_TUTRIAL:
		_scene = new TutrialScene();
		_st = SType_TUTRIAL;
		_scene->Initialize();
		break;
	case SType_GAME:
		_scene = new GameScene();
		_scene->Initialize();
		_st = SType_GAME;
		break;
	case SType_RESULT:
		_scene = new ResultScene();
		_st = SType_RESULT;
		_scene->Initialize();
		break;
	default:
		break;
	}
}

void SceneManager::setNextSceneType(SCENE_TYPE st)
{
	nextSceneType = st;
}

SCENE_TYPE SceneManager::getNextSceneType()
{
	return nextSceneType;
}

//撃破した数をセット
void SceneManager::SetScore(unsigned int score_) {
	_score = score_;
}
//撃破した数をゲット
unsigned int SceneManager::GetScore() const {
	return _score;
}