#pragma once
//===================================================================
//						SceneManager.h
//					   シーン管理クラス
//===================================================================

//列挙
enum SCENE_TYPE
{
	SType_TITLE,
	SType_GAME,
	SType_RESULT
};

class BaseScene;

//シーン管理クラス
class SceneManager
{
private:
	BaseScene *_scene;		//現在のシーン
	SCENE_TYPE _st;			//現在のシーンタイプ

	//　シングルトン（１つしか作らないもの）------------------------------
	//①新規作成禁止
	SceneManager();		//コンストラクタ
	~SceneManager();	//デストラクタ

	//②コピー禁止
	SceneManager( const SceneManager &Inst );
	
	//③代入禁止
	SceneManager &operator = ( const SceneManager &Inst );


private:
	unsigned int _score;

public:
	//　インスタンス取得---------------------------------------------------
	static SceneManager &GetInstance()
	{
		//staticをつけることで何度宣言してもInstanceは1つしか作成されない
		static SceneManager Instance;
		return Instance;
	}

	//　通常のメソッド-----------------------------------------------------
	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

	void ChangeScene( SCENE_TYPE st );	//シーン切り替え

	//撃破した数をセット
	void SetScore(unsigned int score_);
	//撃破した数をゲット
	unsigned int GetScore() const;
	//　アクセサ-----------------------------------------------------------
	BaseScene *GetScene(){ return _scene; }
};