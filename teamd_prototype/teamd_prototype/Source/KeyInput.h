#pragma once
//===================================================================
//						  KeyInput.h
//						�L�[���̓N���X
//===================================================================

class KeyInput
{
private:
	char nowKey[ 256 ], oldKey[ 256 ];	//�ŐV�̃L�[���A�P�t���[���O�̃L�[���

	//�@�V���O���g���i�P�������Ȃ����́j------------------------------
	//�@�V�K�쐬�֎~
	KeyInput();		//�R���X�g���N�^
	~KeyInput();	//�f�X�g���N�^

	//�A�R�s�[�֎~
	KeyInput( const KeyInput &Inst );
	
	//�B����֎~
	KeyInput &operator = ( const KeyInput &Inst );

public:
	//�@�C���X�^���X�擾---------------------------------------------------
	static KeyInput &GetInstance()
	{
		//static�����邱�Ƃŉ��x�錾���Ă�Instance��1�����쐬����Ȃ�
		static KeyInput Instance;
		return Instance;
	}

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize	();		//������
	void Finalize	();		//�I������
	void Update		();		//�X�V
	void Draw		();		//�`��

	//�@�L�[�̏��---------------------------------------------------------
	bool GetKey		( int keyCode );	//�L�[��������Ă��邩
	bool GetKeyDown	( int keyCode );	//�L�[�������ꂽ�u��
	bool GetKeyUp	( int keyCode );	//�L�[�������ꂽ�u��
};