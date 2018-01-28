#pragma once
//=====================================================================
//								Fall.h
//						 ���򖗃G�t�F�N�g�N���X
//=====================================================================


//�@�萔---------------------------------------------------------------
const Vector2 FALL_DIV_CNT  = {   5,   3 };	//������
const Vector2 FALL_DIV_SIZE = { 224, 288 };	//�����T�C�Y

class Fall : public Effect
{
private:
	//�@�A�j���[�V����-----------------------------------------------------
	int _animIdx;			//�A�j���[�V�����̃J�E���g
	int _animFall;			//�o�A�j���̑��x

public:
	Fall();	//�R���X�g���N�^
	~Fall();	//�@�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();				//������
	void Initialize( Vector2 pos );	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw(const Vector2& offset_);		//�`��
};