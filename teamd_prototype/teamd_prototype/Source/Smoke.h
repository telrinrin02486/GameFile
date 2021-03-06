#pragma once
//=====================================================================
//								Dust.h
//							煙エフェクトクラス
//=====================================================================


//　定数---------------------------------------------------------------
const Vector2 SMOKE_DIV_CNT  = Vector2{   8,   3 };	//分割数
const Vector2 SMOKE_DIV_SIZE = Vector2{ 256, 256 };	//分割サイズ

class Smoke : public Effect
{
private:
	//　アニメーション-----------------------------------------------------
	int _animIdx;			//アニメーションのカウント
	int _animDust;			//塵アニメの速度

public:
	Smoke();	//コンストラクタ
	~Smoke();	//　デストラクタ

	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Initialize( Vector2 pos );	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw(const Vector2& offset_);		//描画
};