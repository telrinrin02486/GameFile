//===================================================================
//						SceneManager.cpp
//						�V�[���Ǘ��N���X
//===================================================================
using namespace std;

// SceneManager.h
#include "BaseScene.h"
#include "Vector2.h"			// �g�p�Ȃ�
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect�AVector2�Astd
#include "GameScene.h"			// BaseScene�AEffectManager
#include "SceneManager.h"		// BaseScene

//SceneManager.cpp

//-------------------------------------------------------------------
//�@�R���X�g���N�^
//-------------------------------------------------------------------
SceneManager::SceneManager()
{

}

//-------------------------------------------------------------------
//�@�f�X�g���N�^
//-------------------------------------------------------------------
SceneManager::~SceneManager()
{

}

//-------------------------------------------------------------------
//�@������
//-------------------------------------------------------------------
void SceneManager::Initialize()
{
	_scene = new GameScene();
	_st = SType_TITLE;
	_scene->Initialize();
}

//-------------------------------------------------------------------
//�@�I������
//-------------------------------------------------------------------
void SceneManager::Finalize()
{

}

//-------------------------------------------------------------------
//�@�X�V
//-------------------------------------------------------------------
void SceneManager::Update()
{
	_scene->Update();
}

//-------------------------------------------------------------------
//�@�`��
//-------------------------------------------------------------------
void SceneManager::Draw()
{
	_scene->Draw();
}

//-------------------------------------------------------------------
//�@�V�[���؂�ւ�
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