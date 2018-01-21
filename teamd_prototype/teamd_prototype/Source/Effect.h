#pragma once
//=====================================================================
//							   Effect
//							効果基底クラス
//=====================================================================

class Effect
{
protected:
	//　座標系-------------------------------------------------------------
	Vector2	   _pos;			//座標
	Vector2	   _size;			//画像サイズ
	Vector2	   _ext;			//描画倍率
	const int *_img;			//テクスチャ
	bool	   _isDelete;		//消滅フラグ
		    
	//　速度---------------------------------------------------------------
	float _effectSpeed;

public:
	Effect();	//コンストラクタ
	~Effect();	//　デストラクタ

	//純粋仮想関数
	//継承先によって処理が変わる
	//継承先で必ず同じ関数を実装する必要がある
	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw(const Vector2& offset_)			= 0;

	//　アクセサ-----------------------------------------------------------
	Vector2 GetPos()		{ return _pos; }			//座標参照
	Vector2 GetSize()		{ return _size; }			//サイズ参照
	Vector2	GetExt()		{ return _ext;	}			//描画倍率
	bool	IsDelete()		{ return _isDelete; }		//消滅判定参照

	void SetPos	  ( float x, float y )	{ _pos.x = x; _pos.y = y; }		//座標設定
	void SetPos	  ( Vector2 v		 )	{ _pos = v; }
	void SetSize  ( float x, float y )	{ _size.x = x; _size.y = y; }	//サイズ設定
	void SetSize  ( Vector2 v		 )	{ _size = v; }
	void SetExt	  ( float x, float y )	{ _ext.x = x; _ext.y = y; }
	void SetExt	  ( Vector2 v		 )	{ _ext = v; }
	void SetImg	  ( const int *img	 )	{ _img = img; }
	void SetDelete( bool deleteFlg	 )	{ _isDelete = deleteFlg; }
};