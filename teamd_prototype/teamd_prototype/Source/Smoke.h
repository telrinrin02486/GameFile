#pragma once
//=====================================================================
//								Dust.h
//							���G�t�F�N�g�N���X
//=====================================================================


//�@�萔---------------------------------------------------------------
const Vector2 SMOKE_DIV_CNT  = Vector2{   8,   3 };	//������
const Vector2 SMOKE_DIV_SIZE = Vector2{ 256, 256 };	//�����T�C�Y

class Smoke : public Effect
{
private:
	//�@�A�j���[�V����-----------------------------------------------------
	int _animIdx;			//�A�j���[�V�����̃J�E���g
	int _animDust;			//�o�A�j���̑��x

public:
	Smoke();	//�R���X�g���N�^
	~Smoke();	//�@�f�X�g���N�^

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Initialize( Vector2 pos );	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw(const Vector2& offset_);		//�`��
};