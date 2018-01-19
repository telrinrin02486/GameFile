#pragma once


enum UI_ID
{
	ID_title,
	ID_startButtom,
	ID_titleBack,
	ID_MAX
};

typedef struct
{

	int image[ID_MAX];
	Vector2 pos[ID_MAX];

}nakasima;


class TitleScene : public BaseScene
{
private:
	nakasima titleImage[ID_MAX];//title���Ŏg�p����C���[�W
	
public:
	TitleScene();
	~TitleScene();

	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��
};

