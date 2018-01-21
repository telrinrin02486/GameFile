#pragma once
//=====================================================================
//							  ImageMng.cpp
//							 画像管理クラス
//=====================================================================
#include <string>
#include "Vector2.h"
//　定数---------------------------------------------------------------
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

	int image[ID_MAX];
	Vector2 pos[ID_MAX];

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
	void setUIID(std::string fileName, ID_UI ui_d, Vector2 pos);//UIのsetter
	const UI *GetUIID(int ui_id);//UIのgetter
	const int *GetImgDivID(std::string fileName, Vector2 divCnt, Vector2 divSize);
	void UiDraw(ID_UI startID, ID_UI endID);	//Uiのまとめ描画
};

