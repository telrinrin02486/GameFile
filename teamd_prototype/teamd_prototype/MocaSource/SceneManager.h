#pragma once
//===================================================================
//						SceneManager.h
//					   �V�[���Ǘ��N���X
//===================================================================

//��
enum SCENE_TYPE
{
	SType_TITLE,
	SType_GAME,
	SType_RESULT
};

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

	//�@�A�N�Z�T-----------------------------------------------------------
	BaseScene *GetScene(){ return _scene; }
};