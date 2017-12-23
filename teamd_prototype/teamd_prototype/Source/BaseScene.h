#pragma once
//===================================================================
//						BaseScene.h
//					   Base���N���X
//===================================================================

class BaseScene
{
private:

protected:
	int _texID;
	bool _isChange;

public:
	//�������z�֐�
	//�p����ɂ���ď������ς��
	//�p����ŕK�������֐�����������K�v������
	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw()			= 0;
};