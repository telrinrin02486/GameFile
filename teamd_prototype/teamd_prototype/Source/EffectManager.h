#pragma once
//=====================================================================
//							EffectManager.h
//						  エフェクト管理クラス
//=====================================================================
#include <vector>
#include "Vector2.h"
//　定数---------------------------------------------------------------

struct EffectData
{
	char filePath[ 256 ];
	Vector2 divCnt;
	Vector2 divSize;
};

enum EFFECT_TYPE
{
	EFFECT_TYPE_DUST,
	EFFECT_TYPE_SMOKE,
	EFFECT_TYPE_BLOOD,

	EFFECT_TYPE_MAX
};

class Effect;
class EffectManager
{
private:
	std::vector< Effect * > _effects;

	const int *_img[ EFFECT_TYPE_MAX ];

public:
	static EffectManager& Instance() {
		static EffectManager ins;
		return ins;
	}
	


	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void TexLoading();	//アニメーション読み込み
	void Finalize();	//終了処理
	void Update();		//更新処理
	void Draw(const Vector2& offset_);		//描画処理
	void Delete();		//消滅処理

	//　機能---------------------------------------------------------------
	void EffectCreate( Vector2 pos, EFFECT_TYPE effectType );

	//　アクセサ-----------------------------------------------------------
	std::vector< Effect * > *GetEffectList(){ return &_effects; }

private:
	EffectManager();

protected:
	~EffectManager();

};