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
#include "TitleScene.h"	
#include "GameScene.h"			// BaseScene�AEffectManager
#include "ResultScene.h"	
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
	
	//title����̑J�ڂ��킸��킵�����
	//�R�R�̐�����game�ɕς���
	_scene = new TitleScene();
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
	case SType_TITLE:
		_scene = new TitleScene();
		_st = SType_TITLE;
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

void SceneManager::setSceneType(SCENE_TYPE st)
{
	_st = st;
}

SCENE_TYPE SceneManager::getSceneType()
{
	return _st;
}

//���j���������Z�b�g
void SceneManager::SetScore(unsigned int score_) {
	_score = score_;
}
//���j���������Q�b�g
unsigned int SceneManager::GetScore() const {
	return _score;
}