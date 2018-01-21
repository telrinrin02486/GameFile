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
	_imageDivList = new int[IMG_LIST_SIZE];
	_nameDivList = new string[IMG_LIST_SIZE];

	//������
	for (int i = 0; i < IMG_LIST_SIZE; i++)
	{
		_imageDivList[i] = 0;
		_nameDivList[i] = "";
	}

	//�擪�̓G���[�R�[�h�Ƃ���
	_imageDivList[0] = -1;


	//titleUI�A�w�i�̃��[�h
	setUIID("../image/sceneBack/title/titleBack.png", ID_titleBack, { 0, 0 });
	setUIID("../image/UI/title/titleImage.png", ID_title, { 400, 480 / 5 });
	setUIID("../image/UI/title/startButtom.png", ID_startButtom, { 475, 480 / 2 });

	//resultUI�A�w�i�̃��[�h
	setUIID("../image/result.png", ID_resultBack, { 0, 0 });
	setUIID("../image/UI/result/resultButtom1.png", ID_resultButtom1, { 1080 / 2, 480 / 3 });
	setUIID("../image/UI/result/resultButtom2.png", ID_resultButtom2, { 1080 / 2, 480 / 2 });

}

//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
ImageMng::~ImageMng()
{
	/*�I���ӁI*/
	//�z���delete�ł͕K��[]������delete���邱��
	//[]�Ȃ����Ɛ擪�����폜����Ȃ��̂��I
	delete[]_imageDivList;
	delete[]_nameDivList;
}

//---------------------------------------------------------------------
//�@����
//---------------------------------------------------------------------
void ImageMng::Create()
{
	if (_Instance == nullptr)
	{
		_Instance = new ImageMng;
	}
}

//---------------------------------------------------------------------
//�@�폜
//---------------------------------------------------------------------
void ImageMng::Destroy()
{
	if (_Instance != nullptr)
	{
		delete _Instance;
	}

	_Instance = nullptr;
}

void ImageMng::setUIID(std::string fileName, ID_UI ui_id, Vector2 pos)
{
	uiList[ui_id].image[ui_id] = LoadGraph(fileName.c_str());
	uiList[ui_id].pos[ui_id] = pos;
}

const UI *ImageMng::GetUIID(int ui_id)
{
	return &uiList[ui_id];
}

//---------------------------------------------------------------------
//�@�摜���X�g����C�ӂ̉摜�̐擪��Ԃ�
//---------------------------------------------------------------------
const int *ImageMng::GetImgDivID(string fileName, Vector2 divCnt, Vector2 divSize)
{
	int listIdx;		//���X�g�v�f��

						//�ǂݍ��ݍς݂��`�F�b�N
	for (listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++)
	{
		if (_nameDivList[listIdx] == fileName)
		{
			return &_imageDivList[listIdx];
		}
	}

	//���g�p�̈��T��
	bool flg = false;	//�V�K�ǂݍ��݂ł��邩

	for (listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++)
	{
		if (_imageDivList[listIdx] == 0)
		{
			flg = true;

			//�v�f���`�F�b�N
			if (listIdx + divCnt.x * divCnt.y >= IMG_LIST_SIZE)
			{
				flg = false;
				break;
			}

			//���g�p�`�F�b�N
			for (int i = 1; i < divCnt.x * divCnt.y; i++)
			{
				if (_imageDivList[listIdx + i] != 0)
				{
					flg = false;
					listIdx += i;
					break;
				}
			}

			//����������T���I��
			if (flg)
			{
				break;
			}
		}
	}

	if (flg)
	{
		//�擪��ۑ�
		_nameDivList[listIdx] = fileName;

		//�摜�̃��[�h
		if (LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y,
			divCnt.x, divCnt.y, divSize.x, divSize.y, &_imageDivList[listIdx], false) == -1)
		{

			exit(1);
		}

		return &_imageDivList[listIdx];
	}
	else
	{
		//�G���[(-1)��Ԃ�
		return &_imageDivList[0];
	}

}


void ImageMng::UiDraw(ID_UI startID, ID_UI endID)
{
	int id = startID;
	while (id < endID)
	{
		DrawGraph(GetUIID(id)->pos[id].x, GetUIID(id)->pos[id].y, GetUIID(id)->image[id], true);
		id++;
	}

}