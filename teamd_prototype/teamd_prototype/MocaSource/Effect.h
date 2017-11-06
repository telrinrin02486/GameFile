#pragma once
//=====================================================================
//							   Effect.h
//							���ʊ��N���X
//=====================================================================

class Effect
{
protected:
	//�@���W�n-------------------------------------------------------------
	Vector2	   _pos;			//���W
	Vector2	   _size;			//�摜�T�C�Y
	Vector2	   _ext;			//�`��{��
	const int *_img;			//�e�N�X�`��
	bool	   _isDelete;		//���Ńt���O
		    
	//�@���x---------------------------------------------------------------
	float _effectSpeed;

public:
	Effect();	//�R���X�g���N�^
	~Effect();	//�@�f�X�g���N�^

	//�������z�֐�
	//�p����ɂ���ď������ς��
	//�p����ŕK�������֐�����������K�v������
	virtual void Initialize()	= 0;
	virtual void Update()		= 0;
	virtual void Draw()			= 0;

	//�@�A�N�Z�T-----------------------------------------------------------
	Vector2 GetPos()		{ return _pos; }			//���W�Q��
	Vector2 GetSize()		{ return _size; }			//�T�C�Y�Q��
	Vector2	GetExt()		{ return _ext;	}			//�`��{��
	bool	IsDelete()		{ return _isDelete; }		//���Ŕ���Q��

	void SetPos	  ( float x, float y )	{ _pos.x = x; _pos.y = y; }		//���W�ݒ�
	void SetPos	  ( Vector2 v		 )	{ _pos = v; }
	void SetSize  ( float x, float y )	{ _size.x = x; _size.y = y; }	//�T�C�Y�ݒ�
	void SetSize  ( Vector2 v		 )	{ _size = v; }
	void SetExt	  ( float x, float y )	{ _ext.x = x; _ext.y = y; }
	void SetExt	  ( Vector2 v		 )	{ _ext = v; }
	void SetImg	  ( const int *img	 )	{ _img = img; }
	void SetDelete( bool deleteFlg	 )	{ _isDelete = deleteFlg; }
};