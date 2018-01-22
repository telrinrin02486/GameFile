#pragma once
//=====================================================================
//							  ImageMng.cpp
//							 �摜�Ǘ��N���X
//=====================================================================
#include <string>
#include "Vector2.h"
//�@�萔---------------------------------------------------------------
#define IMG_LIST_SIZE 100

enum ID_UI
{
	ID_titleBack,
	ID_title,
	ID_startButtom,
	ID_resultBack,
	ID_resultButtom1,
	ID_resultButtom2,
	ID_MAX
};

typedef struct
{

	int image;
	Vector2 posL;//����
	Vector2 posR;//�E��

}UI;

//---------------------------------------------------------------------
//�@�N���X�F�摜�Ǘ�
//---------------------------------------------------------------------
class ImageMng
{
private:

	UI uiList[ID_MAX];				//�e�V�[����UI���X�g
	int	   *_imageDivList;			//�A�j���[�V�����摜���X�g
	std::string *_nameDivList;		//�摜�p�X���X�g

									//�@�V���O���g���i�P�������Ȃ����́j-----------------------------
	ImageMng();		//�R���X�g���N�^

	static ImageMng *_Instance;		//�C���X�^���X

public:
	~ImageMng();	//�f�X�g���N�^

					//�@�V���O���g���i�P�������Ȃ����́j-----------------------------
	static void Create();		//����
	static void Destroy();		//�폜

								//�C���X�^���X�擾
	static ImageMng *GetInstance()
	{
		return _Instance;
	}

	//�@�@�\---------------------------------------------------------------
	void setUIID(std::string fileName, ID_UI ui_id, Vector2 posL, Vector2 posR);//UI��setter
	const UI *GetUIID(int ui_id);//UI��getter
	const int *GetImgDivID(std::string fileName, Vector2 divCnt, Vector2 divSize);
	void UiDraw(ID_UI startID, ID_UI endID);	//Ui�̂܂Ƃߕ`��
};

