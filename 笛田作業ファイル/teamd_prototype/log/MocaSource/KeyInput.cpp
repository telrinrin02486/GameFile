//===================================================================
//						 KeyInput.cpp
//						キー入力クラス
//===================================================================

// KeyInput.h
#include "KeyInput.h"		// 使用なし

// KeyInput.cpp
#include <string.h>
#include "DxLib.h"

//-------------------------------------------------------------------
//　コンストラクタ
//-------------------------------------------------------------------
KeyInput::KeyInput()
{

}

//-------------------------------------------------------------------
//　デストラクタ
//-------------------------------------------------------------------
KeyInput::~KeyInput()
{

}

//-------------------------------------------------------------------
//　初期化
//-------------------------------------------------------------------
void KeyInput::Initialize()
{
	
}

//-------------------------------------------------------------------
//　終了処理
//-------------------------------------------------------------------
void KeyInput::Finalize()
{

}

//-------------------------------------------------------------------
//　更新
//-------------------------------------------------------------------
void KeyInput::Update()
{
	//更新前のキー入力情報を保存
	memcpy( oldKey, nowKey, sizeof( oldKey ) );

	//最新のキー情報に取得
	DxLib::GetHitKeyStateAll( nowKey );
}

//-------------------------------------------------------------------
//　描画
//-------------------------------------------------------------------
void KeyInput::Draw()
{
	
}

//-------------------------------------------------------------------
//　キーが押されているか
//-------------------------------------------------------------------
bool KeyInput::GetKey( int keyCode )
{
	return nowKey[ keyCode ];
}

//-------------------------------------------------------------------
//　キーが押された瞬間
//-------------------------------------------------------------------
bool KeyInput::GetKeyDown( int keyCode )
{
	return ( !oldKey[ keyCode ] && nowKey[ keyCode ] );
}

//-------------------------------------------------------------------
//　キーが離された瞬間
//-------------------------------------------------------------------
bool KeyInput::GetKeyUp( int keyCode )
{
	return ( oldKey[ keyCode ] && !nowKey[ keyCode ] );
}