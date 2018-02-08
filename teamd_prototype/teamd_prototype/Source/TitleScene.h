#pragma once
#include "ImageMng.h"


class TitleScene : public BaseScene
{
private:
	int nowPad,oldPad;

public:
	TitleScene();
	~TitleScene();

	void Initialize();	//‰Šú‰»
	void Finalize();	//I—¹ˆ—
	void Update();		//XV
	void Draw();		//•`‰æ

};

