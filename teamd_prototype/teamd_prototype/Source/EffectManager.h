#pragma once
//=====================================================================
//							EffectManager.h
//						  �G�t�F�N�g�Ǘ��N���X
//=====================================================================
#include <vector>
#include "Vector2.h"
//�@�萔---------------------------------------------------------------

struct EffectData
{
	char filePath[ 256 ];
	Vector2 divCnt;
	Vector2 divSize;
};

enum EFFECT_TYPE
{
	EFFECT_TYPE_DUST,
	EFFECT_TYPE_SMOKE,
	EFFECT_TYPE_BLOOD,

	EFFECT_TYPE_MAX
};

class Effect;
class EffectManager
{
private:
	std::vector< Effect * > _effects;

	const int *_img[ EFFECT_TYPE_MAX ];

public:
	static EffectManager& Instance() {
		static EffectManager ins;
		return ins;
	}
	


	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void TexLoading();	//�A�j���[�V�����ǂݍ���
	void Finalize();	//�I������
	void Update();		//�X�V����
	void Draw(const Vector2& offset_);		//�`�揈��
	void Delete();		//���ŏ���

	//�@�@�\---------------------------------------------------------------
	void EffectCreate( Vector2 pos, EFFECT_TYPE effectType );

	//�@�A�N�Z�T-----------------------------------------------------------
	std::vector< Effect * > *GetEffectList(){ return &_effects; }

private:
	EffectManager();

protected:
	~EffectManager();

};