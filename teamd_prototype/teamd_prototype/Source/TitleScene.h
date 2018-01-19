#pragma once


enum UI_ID
{
	ID_title,
	ID_startButtom,
	ID_titleBack,
	ID_MAX
};

typedef struct
{

	int image[ID_MAX];
	Vector2 pos[ID_MAX];

}nakasima;


class TitleScene : public BaseScene
{
private:
	nakasima titleImage[ID_MAX];//title内で使用するイメージ
	
public:
	TitleScene();
	~TitleScene();

	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画
};

