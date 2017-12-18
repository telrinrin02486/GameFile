//=====================================================================
//							EffectManager.cpp
//						  エフェクト管理クラス
//=====================================================================
using namespace std;

// EffectManager.h
#include "Vector2.h"			// 使用なし
#include "Effect.h"				// Vector2
#include "Dust.h"				// Effect
#include "Smoke.h"				// Effect
#include "EffectManager.h"		// Effect, Dust, Vector2, std
#include "SoundManager.h"

// EffectManager.cpp
#include "ImageMng.h"			// std, Vector2

#include "DxLib.h"

//　定数---------------------------------------------------------------
const EffectData EffectImgData[ EFFECT_TYPE_MAX ] =
{
	{ "../image/dust.png" , DUST_DIV_CNT , DUST_DIV_SIZE  },
	{ "../image/smoke.png", SMOKE_DIV_CNT, SMOKE_DIV_SIZE }
};

//---------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------
EffectManager::EffectManager()
{
	TexLoading();
	Initialize();
}

//---------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------
EffectManager::~EffectManager()
{

}

//---------------------------------------------------------------------
//　初期化
//---------------------------------------------------------------------
void EffectManager::Initialize()
{

}

//---------------------------------------------------------------------
//　アニメーション読み込み
//---------------------------------------------------------------------
void EffectManager::TexLoading()
{
	//テクスチャのロード
	for ( int i = 0; i < EFFECT_TYPE_MAX; i++ )
	{
		_img[ i ] = ImageMng::GetInstance()->GetImgID( EffectImgData[ i ].filePath, EffectImgData[ i ].divCnt, EffectImgData[ i ].divSize );
	}
}

//---------------------------------------------------------------------
//　終了処理
//---------------------------------------------------------------------
void EffectManager::Finalize()
{

}

//---------------------------------------------------------------------
//　更新処理
//---------------------------------------------------------------------
void EffectManager::Update()
{
	//イテレータ
	//ベクタ配列の要素にアクセスするためのもの
	vector< Effect * >::iterator itr;

	//エフェクトすべてを更新
	for ( itr = _effects.begin(); itr != _effects.end(); itr++ )
	{
		( *itr )->Update();
	}
}

//---------------------------------------------------------------------
//　描画処理
//---------------------------------------------------------------------
void EffectManager::Draw()
{
	//イテレータ
	//ベクタ配列の要素にアクセスするためのもの
	vector< Effect * >::iterator itr;

	//エフェクトすべてを描画
	for ( itr = _effects.begin(); itr != _effects.end(); itr++ )
	{
		( *itr )->Draw();
	}
}

//---------------------------------------------------------------------
//　消滅処理
//---------------------------------------------------------------------
void EffectManager::Delete()
{
	//イテレータ
	//ベクタ配列の要素にアクセスするためのもの
	vector< Effect * >::iterator itr;

	//エフェクトの削除（本体の削除とリストからの除外）
	for ( itr = _effects.begin(); itr != _effects.end(); )
	{
		if ( ( *itr )->IsDelete() )
		{
			Effect *enemyPtr = ( *itr );
			itr = _effects.erase( itr );	//リストから除外し、次の要素を繋ぐ
			delete( enemyPtr );				//本体の削除
		}
		else
		{
			itr++;	//次へ
		}
	}
}

//---------------------------------------------------------------------
//　エフェクトの生成
//---------------------------------------------------------------------
void EffectManager::EffectCreate( Vector2 pos, EFFECT_TYPE effectType )
{
	SoundManager& soundMng = SoundManager::GetInstance();
	switch ( effectType )
	{
	case EFFECT_TYPE_DUST:
	{
		Dust *newDust = new Dust();
		newDust->Initialize( pos );
		newDust->SetImg( _img[ EFFECT_TYPE_DUST ] );
		_effects.push_back( newDust );
	}
		break;

	case EFFECT_TYPE_SMOKE:
	{
		Smoke *newSmoke = new Smoke();
		newSmoke->Initialize( pos );
		newSmoke->SetImg( _img[ EFFECT_TYPE_SMOKE ] );
		_effects.push_back( newSmoke );
		soundMng.Play(SOUND_TYPE::EXPLOSION);
	}
		break;

	case EFFECT_TYPE_MAX:
		break;

	default:
		break;
	}
}