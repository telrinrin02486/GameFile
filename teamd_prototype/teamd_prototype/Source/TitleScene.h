#pragma once
class TitleScene : public BaseScene
{
private:
	int titleImage;
	int startButtom;
public:
	TitleScene();
	~TitleScene();

	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画
};

