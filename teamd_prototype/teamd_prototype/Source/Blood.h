#pragma once
//=====================================================================
//								Blood.h
//						 ���򖗃G�t�F�N�g�N���X
//=====================================================================


//�@�萔---------------------------------------------------------------
const VECTOR2 BLOOD_DIV_CNT  = {   5,   3 };	//������
const VECTOR2 BLOOD_DIV_SIZE = { 256, 256 };	//�����T�C�Y

class Blood : public Effect
{
private:
	//�@�A�j���[�V����-----------------------------------------------------
	int _animIdx;			//�A�j���[�V�����̃J�E���g
	int _animBlood;			//�o�A�j���̑��x

public:
	Blood();	//�R���X�g���N�^
	~Blood();	//�@�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();				//������
	void Initialize( VECTOR2 pos );	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��
};