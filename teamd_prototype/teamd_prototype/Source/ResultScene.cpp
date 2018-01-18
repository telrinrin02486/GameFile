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

	//�w�i�摜�����[�h
	resultButtom1 = LoadGraph("../image/UI/result/resultButtom1.png");
	resultButtom2 = LoadGraph("../image/UI/result/resultButtom2.png");
	backImg		  = LoadGraph("../image/result.png");

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
	//title��
	if (key.GetKeyUp(KEY_INPUT_2))
	{
		SceneManager::GetInstance().ChangeScene(SType_TITLE);
	}
	//game��
	if (key.GetKeyUp(KEY_INPUT_3))
	{
		SceneManager::GetInstance().ChangeScene(SType_GAME);
	}


}

//---------------------------------------------------------------------
//�@�`��
//---------------------------------------------------------------------
void ResultScene::Draw()
{
	//�w�i��`�悷�邺
	DrawGraph(1080 / 2, 480 / 3, resultButtom1, true);
	DrawGraph(1080 / 2, 480 / 2, resultButtom2, true);
	DrawGraph(0, 0, backImg, false);
	DxLib::DrawGraph(0, 0, _texID, false);	//�w�i
	DrawFormatString(250, 250, 0xffffff00, "�j��X�R�A�F%d", SceneManager::GetInstance().GetScore());

}
