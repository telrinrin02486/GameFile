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

	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};