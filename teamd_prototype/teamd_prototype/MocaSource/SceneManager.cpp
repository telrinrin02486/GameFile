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
#include "GameScene.h"			// BaseScene、EffectManager
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
	_scene = new GameScene();
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
	case SType_GAME:
		_scene = new GameScene();
		_scene->Initialize();
		_st = SType_GAME;
		break;

	default:
		break;
	}
}