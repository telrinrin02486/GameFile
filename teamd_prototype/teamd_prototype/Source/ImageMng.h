#pragma once
//=====================================================================
//							  ImageMng.cpp
//							 画像管理クラス
//=====================================================================
#include <string>
#include "Vector2.h"
//　定数---------------------------------------------------------------
#define IMG_LIST_SIZE 100

//---------------------------------------------------------------------
//　クラス：画像管理
//---------------------------------------------------------------------
class ImageMng
{
private:
	int	   *_imageList;				//画像リスト
	std::string *_nameList;				//画像パスリスト

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
	const int *GetImgID( std::string fileName, Vector2 divCnt, Vector2 divSize );
};

