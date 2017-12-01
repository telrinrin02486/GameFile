//===================================================================
//
//								main.cpp
//				�G���g���[�|�C���g�ƃ��C�u�����̏�����
//
//===================================================================
using namespace std;

// main.cpp
#include "BaseScene.h"
#include "SceneManager.h"		// BaseScene
#include "SoundManager.h"

#include "Vector2.h"			// �g�p�Ȃ�
#include "ImageMng.h"			// std, Vector2

#include "KeyInput.h"
#include "Camera.h"
#include "DxLib.h"

#include "Const.h"


int main(void)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode( true );
	SetTransColor( 255, 0, 255 );
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);

	//DxLib�̏�����
	if ( DxLib::DxLib_Init() == -1 )
	{
		return -1;
	}

	//�Q�[���̏�����
	ImageMng::GetInstance()->Create();
	SceneManager::GetInstance().Initialize();
	SoundManager::GetInstance().Initialize();

	Camera::Instance();

	while ( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		
		//	�Q�[���̐���E�X�V-------------------------------------------------
		KeyInput::GetInstance().Update();		//�@�L�[���͂̍X�V
		SceneManager::GetInstance().Update();	//�V�[���̍X�V
		Camera::Instance().Update();			//�J����


		//	�Q�[���̕`��@-----------------------------------------------------
		ClearDrawScreen();					//��ʂ̏�����
		SceneManager::GetInstance().Draw();	//�V�[���̕`��
		ScreenFlip();						//��ʂ̍X�V
	}

	//DxLib�̏I������
	DxLib::DxLib_End();

	return 0;
}