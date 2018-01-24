//=====================================================================
//						  TutrialScene.cpp
//						�Q�[���Ǘ��N���X
//=====================================================================
using namespace std;

// TutrialScene.h
#include "BaseScene.h"
#include "Vector2.h"			// �g�p�Ȃ�
#include "Effect.h"				// Vector2
#include "EffectManager.h"		// Effect�AVector2�Astd
#include "ImageMng.h"
#include "TutrialScene.h"		// BaseScene�AEffectManager

// TutrialScene.cpp
#include "KeyInput.h"			// �g�p�Ȃ�
#include "DxLib.h"

#include "Camera.h"

#include "Player.h"
#include "CB_1.h"
#include "../House.h"			//�Ȃ������������������Ȃ��Ɣ������Ȃ��B��H
#include "EnemyNyn.h"

#include "Collision.h"
#include "SceneManager.h"
#include "../BloodManager.h"

#include "SoundManager.h"

//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
TutrialScene::TutrialScene()
	:_playerInFrame(170, 50, 0, 0)
{
	
}

//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
TutrialScene::~TutrialScene()
{

}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void TutrialScene::Initialize()
{
	//�w�i�摜�����[�h
	backImg = LoadGraph("../image/sceneBack/tutrial/tutrial.png");
	SceneManager::GetInstance().setSceneType(SType_TITLE);
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void TutrialScene::Finalize()
{
	
}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void TutrialScene::Update()
{
	KeyInput& key = KeyInput::GetInstance();
	//�܂����݂��Ȃ��̂�
	//isScene == SType_TUTORIAL�̏�Ԃ�
	//ENTER�����Ȃ��ł�
	//game
	 if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_TITLE);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getSceneType());
	}
	else
	{
		//key���͂Ȃ�
	}
}
//---------------------------------------------------------------------
//�@���ԃJ�E���g
//---------------------------------------------------------------------
void TutrialScene::TimeCunter()
{
	
}
//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void TutrialScene::Draw()
{
	//�w�i��`�悷�邺
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, backImg, false);
	
}