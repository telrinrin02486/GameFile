#pragma once
#include "ImageMng.h"


class ResultScene : public BaseScene
{
private:
	int resultButtom1;
	int resultButtom2;
	
	int scoreImg;
	int numImg[10];

	int nowPad, oldPad;
public:
	ResultScene();
	~ResultScene();

	void Initialize();	//初期化
	void Finalize();	//終了処理
	void Update();		//更新
	void Draw();		//描画

};