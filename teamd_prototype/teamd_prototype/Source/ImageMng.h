#pragma once
//=====================================================================
//							  ImageMng.cpp
//							 �摜�Ǘ��N���X
//=====================================================================
#include <string>
#include "Vector2.h"
//�@�萔---------------------------------------------------------------
#define IMG_LIST_SIZE 100

//---------------------------------------------------------------------
//�@�N���X�F�摜�Ǘ�
//---------------------------------------------------------------------
class ImageMng
{
private:
	int	   *_imageList;				//�摜���X�g
	std::string *_nameList;				//�摜�p�X���X�g

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
	const int *GetImgID( std::string fileName, Vector2 divCnt, Vector2 divSize );
};

