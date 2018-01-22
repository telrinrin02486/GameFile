#pragma once
//===================================================================
//						SceneManager.h
//					   �V�[���Ǘ��N���X
//===================================================================

//��tutorial
enum SCENE_TYPE
{
	SType_TITLE,
	SType_TUTRIAL,
	SType_GAME,
	SType_RESULT
};

class BaseScene;

//�V�[���Ǘ��N���X
class SceneManager
{
private:
	BaseScene *_scene;		//���݂̃V�[��
	SCENE_TYPE _st;			//���݂̃V�[���^�C�v

	//�@�V���O���g���i�P�������Ȃ����́j------------------------------
	//�@�V�K�쐬�֎~
	SceneManager();		//�R���X�g���N�^
	~SceneManager();	//�f�X�g���N�^

	//�A�R�s�[�֎~
	SceneManager( const SceneManager &Inst );
	
	//�B����֎~
	SceneManager &operator = ( const SceneManager &Inst );


private:
	unsigned int _score;

public:
	//�@�C���X�^���X�擾---------------------------------------------------
	static SceneManager &GetInstance()
	{
		//static�����邱�Ƃŉ��x�錾���Ă�Instance��1�����쐬����Ȃ�
		static SceneManager Instance;
		return Instance;
	}

	//�@�ʏ�̃��\�b�h-----------------------------------------------------
	void Initialize();	//������
	void Finalize();	//�I������
	void Update();		//�X�V
	void Draw();		//�`��

	void ChangeScene( SCENE_TYPE st );	//�V�[���؂�ւ�

	void setSceneType(SCENE_TYPE st);		//�V�[���̃Z�b�g
	SCENE_TYPE getSceneType();

	//���j���������Z�b�g
	void SetScore(unsigned int score_);
	//���j���������Q�b�g
	unsigned int GetScore() const;
	//�@�A�N�Z�T-----------------------------------------------------------
	BaseScene *GetScene(){ return _scene; }
};