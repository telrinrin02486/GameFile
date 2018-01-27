#pragma once
//=====================================================================
//								BloodE.h
//						 血飛沫エフェクトクラス
//=====================================================================


//　定数---------------------------------------------------------------
const Vector2 BLOOD_DIV_CNT  = {   5,   3 };	//分割数
const Vector2 BLOOD_DIV_SIZE = { 256, 256 };	//分割サイズ

class BloodE : public Effect
{
private:
	//　アニメーション-----------------------------------------------------
	int _animIdx;			//アニメーションのカウント
	int _animBlood;			//塵アニメの速度

public:
	BloodE();	//コンストラクタ
	~BloodE();	//　デストラクタ

	//　通常のメソッド-----------------------------------------------------
	void Initialize();				//初期化
	void Initialize( Vector2 pos );	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw(const Vector2& offset_);		//描画
};