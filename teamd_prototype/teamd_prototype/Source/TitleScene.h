#pragma once
class TitleScene : public BaseScene
{
private:
	int titleImage;
	int startButtom;
public:
	TitleScene();
	~TitleScene();

	void Initialize();	//‰Šú‰»
	void Finalize();	//I—¹ˆ—
	void Update();		//XV
	void Draw();		//•`‰æ
};

