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

	//�w�i�摜�����[�h
	titleImage[ID_title]		= LoadGraph("../image/UI/title/titleImage.png");
	titleImage[ID_startButtom]	= LoadGraph("../image/UI/title/startButtom.png");
	titleImage[ID_titleBack]	= LoadGraph("../image/sceneBack/title/titleBack.png");

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
	
	KeyInput& key = KeyInput::GetInstance();
	//title��
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_GAME);
	}
	
}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void TitleScene::Draw()
{
	//�w�i��`�悷�邺
	DrawGraph(0, 0, titleImage[ID_titleBack], false);
	DrawGraph(400, 480 / 5, titleImage[ID_title], true);
	DrawGraph(475, 480 / 2, titleImage[ID_startButtom], true);
	
}

