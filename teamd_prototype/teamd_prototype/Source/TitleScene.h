#pragma once
#include "ImageMng.h"


class TitleScene : public BaseScene
{
private:
	int nowPad,oldPad;

public:
	TitleScene();
	~TitleScene();

	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

};

