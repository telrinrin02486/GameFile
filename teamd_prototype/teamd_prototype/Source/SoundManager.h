#pragma once


//sound�̎��
//�܂��ǉ����Ă܂���
enum SOUND_TYPE
{
	BGM_TUTRIAL,	//tutrialBGM
	BGM_TITLE,		//titleBGM
	BGM_RESULT,		//resultBGM
	BGM_GAME,		//gameBGM
	BUTTON_1,
	BUTTON_2,
	SS_1,
	SS_2,
	SE_WHISTLE,
	SE_STEPS,
	SCR_MAN,
	SCR_WOMAN,

	HIT_1,
	TENKA,
	EXPLOSION,

	SOUND_MAX

};

class SoundManager
{
private:

	int sound[SOUND_MAX];

	
	SoundManager();		
	~SoundManager();	
	SoundManager(const SoundManager &Inst);				
	SoundManager & operator=(const SoundManager &Inst); 

public:

	
	static SoundManager &GetInstance()
	{
		static SoundManager Instance;
		return Instance;
	}

	void Initialize();
	void Play(SOUND_TYPE _type, int _volume = 128);			//�w��sound�̍Đ�(1��)
	void PlayLoop(SOUND_TYPE _type, int _volume = 128);		//�w��sound�̍Đ�(Loop)
	bool PlayCheak(SOUND_TYPE _type);						//�w��sound�̍Đ�Cheak
	void Stop(SOUND_TYPE _type);							//�Đ���sound�̒�~
};

