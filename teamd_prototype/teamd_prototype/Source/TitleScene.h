#pragma once
#include "ImageMng.h"


class TitleScene : public BaseScene
{
private:
	int nowPad,oldPad;

public:
	TitleScene();
	~TitleScene();

	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

};

