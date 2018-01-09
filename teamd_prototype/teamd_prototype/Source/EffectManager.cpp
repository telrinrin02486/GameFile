//=====================================================================
//							EffectManager.cpp
//						  �G�t�F�N�g�Ǘ��N���X
//=====================================================================
using namespace std;

// EffectManager.h
#include "Vector2.h"			// �g�p�Ȃ�
#include "Effect.h"				// Vector2
#include "Dust.h"				// Effect
#include "Smoke.h"				// Effect
#include "EffectManager.h"		// Effect, Dust, Vector2, std
#include "SoundManager.h"

// EffectManager.cpp
#include "ImageMng.h"			// std, Vector2

#include "DxLib.h"

//�@�萔---------------------------------------------------------------
const EffectData EffectImgData[ EFFECT_TYPE_MAX ] =
{
	{ "../image/dust.png" , DUST_DIV_CNT , DUST_DIV_SIZE  },
	{ "../image/smoke.png", SMOKE_DIV_CNT, SMOKE_DIV_SIZE }
};

//---------------------------------------------------------------------
//�@�R���X�g���N�^
//---------------------------------------------------------------------
EffectManager::EffectManager()
{
	TexLoading();
	Initialize();
}

//---------------------------------------------------------------------
//�@�f�X�g���N�^
//---------------------------------------------------------------------
EffectManager::~EffectManager()
{

}

//---------------------------------------------------------------------
//�@������
//---------------------------------------------------------------------
void EffectManager::Initialize()
{

}

//---------------------------------------------------------------------
//�@�A�j���[�V�����ǂݍ���
//---------------------------------------------------------------------
void EffectManager::TexLoading()
{
	//�e�N�X�`���̃��[�h
	for ( int i = 0; i < EFFECT_TYPE_MAX; i++ )
	{
		_img[ i ] = ImageMng::GetInstance()->GetImgID( EffectImgData[ i ].filePath, EffectImgData[ i ].divCnt, EffectImgData[ i ].divSize );
	}
}

//---------------------------------------------------------------------
//�@�I������
//---------------------------------------------------------------------
void EffectManager::Finalize()
{

}

//---------------------------------------------------------------------
//�@�X�V����
//---------------------------------------------------------------------
void EffectManager::Update()
{
	//�C�e���[�^
	//�x�N�^�z��̗v�f�ɃA�N�Z�X���邽�߂̂���
	vector< Effect * >::iterator itr;

	//�G�t�F�N�g���ׂĂ��X�V
	for ( itr = _effects.begin(); itr != _effects.end(); itr++ )
	{
		( *itr )->Update();
	}
}

//---------------------------------------------------------------------
//�@�`�揈��
//---------------------------------------------------------------------
void EffectManager::Draw()
{
	//�C�e���[�^
	//�x�N�^�z��̗v�f�ɃA�N�Z�X���邽�߂̂���
	vector< Effect * >::iterator itr;

	//�G�t�F�N�g���ׂĂ�`��
	for ( itr = _effects.begin(); itr != _effects.end(); itr++ )
	{
		( *itr )->Draw();
	}
}

//---------------------------------------------------------------------
//�@���ŏ���
//---------------------------------------------------------------------
void EffectManager::Delete()
{
	//�C�e���[�^
	//�x�N�^�z��̗v�f�ɃA�N�Z�X���邽�߂̂���
	vector< Effect * >::iterator itr;

	//�G�t�F�N�g�̍폜�i�{�̂̍폜�ƃ��X�g����̏��O�j
	for ( itr = _effects.begin(); itr != _effects.end(); )
	{
		if ( ( *itr )->IsDelete() )
		{
			Effect *enemyPtr = ( *itr );
			itr = _effects.erase( itr );	//���X�g���珜�O���A���̗v�f���q��
			delete( enemyPtr );				//�{�̂̍폜
		}
		else
		{
			itr++;	//����
		}
	}
}

//---------------------------------------------------------------------
//�@�G�t�F�N�g�̐���
//---------------------------------------------------------------------
void EffectManager::EffectCreate( Vector2 pos, EFFECT_TYPE effectType )
{
	SoundManager& soundMng = SoundManager::GetInstance();
	switch ( effectType )
	{
	case EFFECT_TYPE_DUST:
	{
		Dust *newDust = new Dust();
		newDust->Initialize( pos );
		newDust->SetImg( _img[ EFFECT_TYPE_DUST ] );
		_effects.push_back( newDust );
	}
		break;

	case EFFECT_TYPE_SMOKE:
	{
		Smoke *newSmoke = new Smoke();
		newSmoke->Initialize( pos );
		newSmoke->SetImg( _img[ EFFECT_TYPE_SMOKE ] );
		_effects.push_back( newSmoke );
		soundMng.Play(SOUND_TYPE::EXPLOSION);
	}
		break;

	case EFFECT_TYPE_MAX:
		break;

	default:
		break;
	}
}