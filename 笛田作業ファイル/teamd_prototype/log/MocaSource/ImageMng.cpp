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
	_imageList = new int   [ IMG_LIST_SIZE ];
	_nameList  = new string[ IMG_LIST_SIZE ];

	//初期化
	for ( int i = 0; i < IMG_LIST_SIZE; i++ )
	{
		_imageList[ i ] = 0;
		_nameList [ i ] = "";
	}

	//先頭はエラーコードとする
	_imageList[ 0 ] = -1;
}
 
//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
ImageMng::~ImageMng()
{
	/*！注意！*/
	//配列のdeleteでは必ず[]をつけてdeleteすること
	//[]なしだと先頭しか削除されないのだ！
	delete []_imageList;
	delete []_nameList;
}

//---------------------------------------------------------------------
//　生成
//---------------------------------------------------------------------
void ImageMng::Create()
{
	if ( _Instance == nullptr )
	{
		_Instance = new ImageMng;
	}
}

//---------------------------------------------------------------------
//　削除
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
//　画像リストから任意の画像の先頭を返す
//---------------------------------------------------------------------
const int *ImageMng::GetImgID( string fileName, Vector2 divCnt, Vector2 divSize )
{
	int listIdx;		//リスト要素数

	//読み込み済みかチェック
	for ( listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++ )
	{
		if ( _nameList[ listIdx ] == fileName )
		{
			return &_imageList[ listIdx ];
		}
	}

	//未使用領域を探索
	bool flg = false;	//新規読み込みできるか

	for ( listIdx = 0; listIdx < IMG_LIST_SIZE; listIdx++ )
	{
		if ( _imageList[ listIdx ] == 0 )
		{
			flg = true;

			//要素数チェック
			if ( listIdx + divCnt.x * divCnt.y >= IMG_LIST_SIZE )
			{
				flg = false;
				break;
			}

			//未使用チェック
			for ( int i = 1; i < divCnt.x * divCnt.y; i++ )
			{
				if ( _imageList[ listIdx + i ] != 0 )
				{
					flg = false;
					listIdx += i;
					break;
				}
			}

			//見つかったら探索終了
			if ( flg )
			{
				break;
			}
		}
	}

	if ( flg )
	{
		//先頭を保存
		_nameList[ listIdx ] = fileName;

		//画像のロード
		if ( LoadDivGraph( fileName.c_str(), divCnt.x * divCnt.y,
							divCnt.x, divCnt.y, divSize.x, divSize.y, &_imageList[ listIdx ], false ) == -1 )
		{

			exit( 1 );
		}

		return &_imageList[ listIdx ];
	}
	else
	{
		//エラー(-1)を返す
		return &_imageList[ 0 ];
	}
	
}