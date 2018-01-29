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
	SceneManager::GetInstance().setNextSceneType(SType_GAME);
	SoundManager::GetInstance().PlayLoop(BGM_RESULT);

	scoreImg = LoadGraph("../image/Score.png");

	LoadDivGraph("../image/Num.png", 10, 10, 1, 22, 36, numImg);


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
		SceneManager::GetInstance().setNextSceneType(SType_GAME);
		SoundManager::GetInstance().Play(BUTTON_1);
	}
	//tutrial
	else if (key.GetKeyUp(KEY_INPUT_DOWN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x + 150,buttomPos2.y + 50 });
		SceneManager::GetInstance().setNextSceneType(SType_TITLE);
		SoundManager::GetInstance().Play(BUTTON_1);
	}

	else if (key.GetKeyUp(KEY_INPUT_RETURN))
	{
		ImageMng::GetInstance()->setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });
		SoundManager::GetInstance().Stop(BGM_RESULT);
		SoundManager::GetInstance().Play(BUTTON_2);
		SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().getNextSceneType());
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
	ImageMng *ui = ImageMng::GetInstance();
	//�w�i��`�悷�邺
	ui->UiDraw(ID_resultBack, ID_resultButtom2,maskCnt);
	//�w�i�}�X�N
	DrawExtendGraph(ui->GetUIID(ID_resultBackMask)->posL.x, ui->GetUIID(ID_resultBackMask)->posL.y,
					ui->GetUIID(ID_resultBackMask)->posR.x, ui->GetUIID(ID_resultBackMask)->posR.y,
					ui->GetUIID(ID_resultBackMask)->image, true);

	//�X�R�A
	//DrawFormatString(250, 250, 0xffffff00, "�j��X�R�A�F%d", SceneManager::GetInstance().GetScore());

	DrawGraph(200, 200, scoreImg, true);

	DrawGraph(310, 200, numImg[(SceneManager::GetInstance().GetScore() / 100) % 10], true);
	DrawGraph(346, 200, numImg[(SceneManager::GetInstance().GetScore() / 10) % 10], true);
	DrawGraph(382, 200, numImg[(SceneManager::GetInstance().GetScore() / 1) % 10], true);

}

