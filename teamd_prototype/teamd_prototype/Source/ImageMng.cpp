//=====================================================================
//							  ImageMng.cpp
//							 画像管理クラス
//=====================================================================
using namespace std;

//ImageMng.h
#include "Vector2.h"	// 使用なし
#include "ImageMng.h"	// std, Vector2

//ImageMng.cpp
#include "DxLib.h"

//　前方宣言-----------------------------------------------------------
ImageMng *ImageMng::_Instance = nullptr;		//インスタンス

//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
ImageMng::ImageMng()
{
	//インスタンス
	_imageDivList = new int[IMG_LIST_SIZE];
	_nameDivList = new string[IMG_LIST_SIZE];

	//初期化
	for (int i = 0; i < IMG_LIST_SIZE; i++)
	{
		_imageDivList[i] = 0;
		_nameDivList[i] = "";
	}

	//先頭はエラーコードとする
	_imageDivList[0] = -1;

	//maskのロード
	setUIID("../image/UI/mask/mask.png", ID_mask, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x + 150,buttomPos1.y + 50 });

	//titleUI、背景のロード
	setUIID("../image/sceneBack/title/titleBack.png", ID_titleBack, { 0, 0 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/title/titleImage.png", ID_title, { titlePos.x, titlePos.y }, { titlePos.x +350,titlePos.y +100});
	setUIID("../image/UI/title/startButtom.png", ID_startButtom, { buttomPos1.x, buttomPos1.y }, { buttomPos1.x +150,buttomPos1.y +50});
	setUIID("../image/UI/title/tutorialButtom.png", ID_tutorialButtom, { buttomPos2.x, buttomPos2.y }, { buttomPos2.x +150, buttomPos2.y + 50});

	//tutrialUI
	setUIID("../image/UI/mask/tutrialMask.png", ID_tut_mask, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/yazirusi.png", ID_tut_yazirusi, { 0, 0 }, { 0,0 });
	setUIID("../image/UI/tutrial/text1.png", ID_tut_text1, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text2.png", ID_tut_text2, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text3.png", ID_tut_text3, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text4.png", ID_tut_text4, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text5.png", ID_tut_text5, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text6.png", ID_tut_text6, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text7.png", ID_tut_text7, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text8.png", ID_tut_text8, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/text9.png", ID_tut_text9, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/tutrial/next.png", ID_tut_next, { 0, 400 }, { WINDOW_WIDTH,WINDOW_HEIGHT });

	//resultUI、背景のロード
	setUIID("../image/UI/result/result.png", ID_resultBack, { 0, 0 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/mask/maskResult.png", ID_resultBackMask, { 0, 0 }, { WINDOW_WIDTH,WINDOW_HEIGHT });
	setUIID("../image/UI/result/resultButtom1.png", ID_resultButtom1, { buttomPos1.x, buttomPos1.y } ,{ buttomPos1.x +150,buttomPos1.y +50});
	setUIID("../image/UI/result/resultButtom2.png", ID_resultButtom2, { buttomPos2.x, buttomPos2.y } ,{ buttomPos2.x +150,buttomPos2.y +50});

}

//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
ImageMng::~ImageMng()
{
	/*！注意！*/
	//配列のdeleteでは必ず[]をつけてdeleteすること
	//[]なしだと先頭しか削除されないのだ！
	delete[]_imageDivList;
	delete[]_nameDivList;
}

//---------------------------------------------------------------------
//　生成
//---------------------------------------------------------------------
void ImageMng::Create()
{
	if (_Instance == nullptr)
	{
		_Instance = new ImageMng;
	}
}

//---------------------------------------------------------------------
//　削除
//---------------------------------------------------------------------
void ImageMng::Destroy()
{
	if (_Instance != nullptr)
	{
		delete _Instance;
	}

	_Instance = nullptr;
}

void ImageMng::setUIID(std::string fileName, ID_UI ui_id, Vector2 posL, Vector2 posR)
{
	uiList[ui_id].image = LoadGraph(fileName.c_str());
	uiList[ui_id].posL = posL;
	uiList[ui_id].posR = posR;
}

const UI *ImageMng::GetUIID(int ui_id)
{
	return &uiList[ui_id];
}

//---------------------------------------------------------------------
//　画像リストから任意の画像の先頭を返す
//---------------------------------------------------------------------
const int *ImageMng::GetImgDivID(string fileName, Vector2 divCnt, Vector2 divSize)
{
	int listIdx;		//リスト要素数

						//読み込み済みかチェック
	for (listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++)
	{
		if (_nameDivList[listIdx] == fileName)
		{
			return &_imageDivList[listIdx];
		}
	}

	//未使用領域を探索
	bool flg = false;	//新規読み込みできるか

	for (listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++)
	{
		if (_imageDivList[listIdx] == 0)
		{
			flg = true;

			//要素数チェック
			if (listIdx + divCnt.x * divCnt.y >= IMG_LIST_SIZE)
			{
				flg = false;
				break;
			}

			//未使用チェック
			for (int i = 1; i < divCnt.x * divCnt.y; i++)
			{
				if (_imageDivList[listIdx + i] != 0)
				{
					flg = false;
					listIdx += i;
					break;
				}
			}

			//見つかったら探索終了
			if (flg)
			{
				break;
			}
		}
	}

	if (flg)
	{
		//先頭を保存
		_nameDivList[listIdx] = fileName;

		//画像のロード
		if (LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y,
			divCnt.x, divCnt.y, divSize.x, divSize.y, &_imageDivList[listIdx], false) == -1)
		{

			exit(1);
		}

		return &_imageDivList[listIdx];
	}
	else
	{
		//エラー(-1)を返す
		return &_imageDivList[0];
	}

}


void ImageMng::UiDraw(ID_UI startID, ID_UI endID, int _maskCnt)
{
	

	int id = startID;
	while (id <= endID)
	{
		DrawExtendGraph(GetUIID(id)->posL.x, GetUIID(id)->posL.y, 
						GetUIID(id)->posR.x, GetUIID(id)->posR.y, 
						GetUIID(id)->image, true);
		id++;
	}
	//最後にmask描画
	if ((_maskCnt / MASK_CNT) % 2 == 0)

	{
		DrawExtendGraph(GetUIID(ID_mask)->posL.x, GetUIID(ID_mask)->posL.y,
			GetUIID(ID_mask)->posR.x, GetUIID(ID_mask)->posR.y,
			GetUIID(ID_mask)->image, true);
	}
}