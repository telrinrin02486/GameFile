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

	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};