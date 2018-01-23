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
	SoundManager::GetInstance().Play(BGM_TITLE);
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void TitleScene::Finalize()
{
	//�e��J��


}

//---------------------------------------------------------------------
//�@�X�V
//---------------------------------------------------------------------
void TitleScene::Update()
{
	SoundManager::GetInstance().Play(BGM_TITLE);
	bool i = SoundManager::GetInstance().PlayCheak(BGM_TITLE);
	KeyInput& key = KeyInput::GetInstance();
	//key���͂�mask��pos��set
	//mask�̏�Ԃ�titl or tutrial�ւ̑J��
	//�J�ڂ���\��̃V�[����ϐ��ŊǗ�
	if (key.GetKeyUp(KEY_INPUT_UP))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_GAME);
	}

	//�܂����݂��Ȃ��̂�
	//isScene == SType_TUTORIAL�̏�Ԃ�
	//ENTER�����Ȃ��ł�
	if (key.GetKeyUp(KEY_INPUT_DOWN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x + 150,buttomPos2.y + 50 });
		SceneManager::GetInstance().setSceneType(SType_TUTRIAL);
	}
	

	//title��
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
//�@�`��
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	//�w�i��`�悷�邺
	ImageMng::GetInstance()->UiDraw(ID_titleBack, ID_tutorialButtom, maskCnt);


}


