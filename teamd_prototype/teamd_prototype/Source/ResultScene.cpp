//=====================================================================
//						  ResultScene.cpp
//						�Q�[���Ǘ��N���X
//=====================================================================
using namespace std;

// ResultScene.h
#include "BaseScene.h"
#include "Vector2.h"		// �g�p�Ȃ�
#include "ResultScene.h"	// BaseScene�AEffectManager

// ResultScene.cpp
#include "KeyInput.h"		
#include "DxLib.h"
#include "SoundManager.h"
#include "SceneManager.h"



//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
ResultScene::ResultScene()
{
}


//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
ResultScene::~ResultScene()
{
}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void ResultScene::Initialize()
{

	//�V�[���؂�ւ��t���O
	_isChange = false;
	maskCnt = 0;
	SceneManager::GetInstance().setSceneType(SType_GAME);
	SoundManager::GetInstance().PlayLoop(BGM_RESULT);
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void ResultScene::Finalize()
{
	//�e��J��


}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void ResultScene::Update()
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
		SceneManager::GetInstance().setSceneType(SType_TITLE);
		SoundManager::GetInstance().Play(BUTTON_1);
	}

	else if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_RESULT);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getSceneType());
	}
	else
	{
		//key���͂Ȃ�
	}

	maskCnt++;
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void ResultScene::Draw()
{
	//�w�i��`�悷�邺
	ImageMng::GetInstance()->UiDraw(ID_resultBack, ID_resultButtom2,maskCnt);
	DrawFormatString(250, 250, 0xffffff00, "�j��X�R�A�F%d", SceneManager::GetInstance().GetScore());

}

