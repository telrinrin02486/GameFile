#pragma once
//===================================================================
//						SceneManager.h
//					   シーン管理クラス
//===================================================================

//列挙
enum SCENE_TYPE
{
	SType_TITLE,
	SType_TUTRIAL,
	SType_GAME,
	SType_RESULT
};

class BaseScene;

//シーン管理クラス
class SceneManager
{
private:
	BaseScene *_scene;			//現在のシーン
	SCENE_TYPE _st;				//現在のシーンタイプ
	SCENE_TYPE nextSceneType;	//遷移予定のシーンタイプ

	//　シングルトン（１つしか作らないもの）------------------------------
	//�@新規作成禁止
	SceneManager();		//コンストラクタ
	~SceneManager();	//デストラクタ

	//�Aコピー禁止
	SceneManager( const SceneManager &Inst );
	
	//�B代入禁止
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

	void setNextSceneType(SCENE_TYPE st);		//遷移予定のシーンタイプのセット
	SCENE_TYPE getNextSceneType();

	//撃破した数をセット
	void SetScore(unsigned int score_);
	//撃破した数をゲット
	unsigned int GetScore() const;
	//　アクセサ-----------------------------------------------------------
	BaseScene *GetScene(){ return _scene; }
};