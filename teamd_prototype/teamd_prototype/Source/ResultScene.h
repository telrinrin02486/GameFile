#pragma once


class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画
};