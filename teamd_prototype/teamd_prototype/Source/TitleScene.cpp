//=====================================================================
//						  TitleScene.cpp
//						�Q�[���Ǘ��N���X
//=====================================================================
using namespace std;

// TitleScene.h
#include "BaseScene.h"
#include "Vector2.h"		// �g�p�Ȃ�
#include "TitleScene.h"		// BaseScene�AEffectManager

// TitleScene.cpp

#include "KeyInput.h"		// �g�p�Ȃ�
#include "DxLib.h"
#include "SoundManager.h"
#include "SceneManager.h"



//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
TitleScene::TitleScene()
{
}

//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void TitleScene::Initialize()
{

	//�V�[���؂�ւ��t���O
	_isChange = false;
	maskCnt = 0;
	SceneManager::GetInstance().setSceneType(SType_GAME);
	SoundManager::GetInstance().PlayLoop(BGM_TITLE);
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void TitleScene::Finalize()
{
}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void TitleScene::Update()
{
	
	KeyInput& key = KeyInput::GetInstance();
	//�܂����݂��Ȃ��̂�
	//isScene == SType_TUTORIAL�̏�Ԃ�
	//ENTER�����Ȃ��ł�
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
		//key���͂Ȃ�
	}

	maskCnt++;
	
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	//�w�i��`�悷�邺
	ImageMng::GetInstance()->UiDraw(ID_titleBack, ID_tutorialButtom, maskCnt);
}


