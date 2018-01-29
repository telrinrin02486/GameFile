#pragma once
//=====================================================================
//							  ImageMng.cpp
//							 画像管理クラス
//=====================================================================
#include <string>
#include "Vector2.h"
//　定数---------------------------------------------------------------
#define IMG_LIST_SIZE 100

//スクリーンサイズ
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 620

//maskの描画時間
#define MASK_CNT 15

//UI_POS
const Vector2 titlePos = {400,120};
const Vector2 buttomPos1 = { 400,250 };
const Vector2 buttomPos2 = { 400,350 };


enum ID_UI
{
	ID_titleBack,
	ID_title,
	ID_startButtom,
	ID_tutorialButtom,

	ID_tut_mask,
	ID_tut_yazirusi,
	ID_tut_text1,
	ID_tut_text2,
	ID_tut_text3,
	ID_tut_text4,
	ID_tut_text5,
	ID_tut_text6,
	ID_tut_text7,
	ID_tut_text8,
	ID_tut_text9,

	ID_resultBack,
	ID_resultButtom1,
	ID_resultButtom2,
	ID_mask,
	ID_resultBackMask,
	ID_MAX
};

typedef struct
{

	int image;
	Vector2 posL;//左上
	Vector2 posR;//右上

}UI;

//---------------------------------------------------------------------
//　クラス：画像管理
//---------------------------------------------------------------------
class ImageMng
{
private:
	
	UI uiList[ID_MAX];				//各シーンのUIリスト
	int	   *_imageDivList;			//アニメーション画像リスト
	std::string *_nameDivList;		//画像パスリスト

									//　シングルトン（１つしか作らないもの）-----------------------------
	ImageMng();		//コンストラクタ

	static ImageMng *_Instance;		//インスタンス

public:
	~ImageMng();	//デストラクタ

					//　シングルトン（１つしか作らないもの）-----------------------------
	static void Create();		//生成
	static void Destroy();		//削除

								//インスタンス取得
	static ImageMng *GetInstance()
	{
		return _Instance;
	}

	//　機能---------------------------------------------------------------
	void setUIID(std::string fileName, ID_UI ui_id, Vector2 posL, Vector2 posR);//UIのsetter
	const UI *GetUIID(int ui_id);//UIのgetter
	const int *GetImgDivID(std::string fileName, Vector2 divCnt, Vector2 divSize);
	void UiDraw(ID_UI startID, ID_UI endID ,int _maskCnt);	//Uiのまとめ描画
};

