#pragma once
#include "ImageMng.h"

class ResultScene : public BaseScene
{
private:
	int resultButtom1;
	int resultButtom2;

public:
	ResultScene();
	~ResultScene();

	void Initialize();	//‰Šú‰»
	void Finalize();	//I—¹ˆ—
	void Update();		//XV
	void Draw();		//•`‰æ

};