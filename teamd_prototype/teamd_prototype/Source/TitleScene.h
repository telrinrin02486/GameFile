#pragma once
class TitleScene : public BaseScene
{
private:
	int titleImage;
	int startButtom;
public:
	TitleScene();
	~TitleScene();

	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��
};

