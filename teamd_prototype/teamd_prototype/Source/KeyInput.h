#pragma once
//===================================================================
//						  KeyInput.h
//						キー入力クラス
//===================================================================

class KeyInput
{
private:
	char nowKey[ 256 ], oldKey[ 256 ];	//最新のキー情報、１フレーム前のキー情報

	//　シングルトン（１つしか作らないもの）------------------------------
	//①新規作成禁止
	KeyInput();		//コンストラクタ
	~KeyInput();	//デストラクタ

	//②コピー禁止
	KeyInput( const KeyInput &Inst );
	
	//③代入禁止
	KeyInput &operator = ( const KeyInput &Inst );

public:
	//　インスタンス取得---------------------------------------------------
	static KeyInput &GetInstance()
	{
		//staticをつけることで何度宣言してもInstanceは1つしか作成されない
		static KeyInput Instance;
		return Instance;
	}

	//　通常のメソッド-----------------------------------------------------
	void Initialize	();		//初期化
	void Finalize	();		//終了処理
	void Update		();		//更新
	void Draw		();		//描画

	//　キーの状態---------------------------------------------------------
	bool GetKey		( int keyCode );	//キーが押されているか
	bool GetKeyDown	( int keyCode );	//キーが押された瞬間
	bool GetKeyUp	( int keyCode );	//キーが離された瞬間
};