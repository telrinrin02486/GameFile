//=====================================================================
//							  ImageMng.cpp
//							 �摜�Ǘ��N���X
//=====================================================================
using namespace std;

//ImageMng.h
#include "Vector2.h"	// �g�p�Ȃ�
#include "ImageMng.h"	// std, Vector2

//ImageMng.cpp
#include "DxLib.h"

//�@�O���錾-----------------------------------------------------------
ImageMng *ImageMng::_Instance = nullptr;		//�C���X�^���X

//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
ImageMng::ImageMng()
{
	//�C���X�^���X
	_imageList = new int   [ IMG_LIST_SIZE ];
	_nameList  = new string[ IMG_LIST_SIZE ];

	//������
	for ( int i = 0; i < IMG_LIST_SIZE; i++ )
	{
		_imageList[ i ] = 0;
		_nameList [ i ] = "";
	}

	//�擪�̓G���[�R�[�h�Ƃ���
	_imageList[ 0 ] = -1;
}
 
//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
ImageMng::~ImageMng()
{
	/*�I���ӁI*/
	//�z���delete�ł͕K��[]������delete���邱��
	//[]�Ȃ����Ɛ擪�����폜����Ȃ��̂��I
	delete []_imageList;
	delete []_nameList;
}

//---------------------------------------------------------------------
//�@����
//---------------------------------------------------------------------
void ImageMng::Create()
{
	if ( _Instance == nullptr )
	{
		_Instance = new ImageMng;
	}
}

//---------------------------------------------------------------------
//�@�폜
//---------------------------------------------------------------------
void ImageMng::Destroy()
{
	if ( _Instance != nullptr )
	{
		delete _Instance;
	}

	_Instance = nullptr;
}

//---------------------------------------------------------------------
//�@�摜���X�g����C�ӂ̉摜�̐擪��Ԃ�
//---------------------------------------------------------------------
const int *ImageMng::GetImgID( string fileName, Vector2 divCnt, Vector2 divSize )
{
	int listIdx;		//���X�g�v�f��

	//�ǂݍ��ݍς݂��`�F�b�N
	for ( listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++ )
	{
		if ( _nameList[ listIdx ] == fileName )
		{
			return &_imageList[ listIdx ];
		}
	}

	//���g�p�̈��T��
	bool flg = false;	//�V�K�ǂݍ��݂ł��邩

	for ( listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++ )
	{
		if ( _imageList[ listIdx ] == 0 )
		{
			flg = true;

			//�v�f���`�F�b�N
			if ( listIdx + divCnt.x * divCnt.y >= IMG_LIST_SIZE )
			{
				flg = false;
				break;
			}

			//���g�p�`�F�b�N
			for ( int i = 1; i < divCnt.x * divCnt.y; i++ )
			{
				if ( _imageList[ listIdx + i ] != 0 )
				{
					flg = false;
					listIdx += i;
					break;
				}
			}

			//����������T���I��
			if ( flg )
			{
				break;
			}
		}
	}

	if ( flg )
	{
		//�擪��ۑ�
		_nameList[ listIdx ] = fileName;

		//�摜�̃��[�h
		if ( LoadDivGraph( fileName.c_str(), divCnt.x * divCnt.y,
							divCnt.x, divCnt.y, divSize.x, divSize.y, &_imageList[ listIdx ], false ) == -1 )
		{

			exit( 1 );
		}

		return &_imageList[ listIdx ];
	}
	else
	{
		//�G���[(-1)��Ԃ�
		return &_imageList[ 0 ];
	}
	
}